
#include "../lib/minishell.h"

int		determine_filetype(t_cmd *cmd_list)
{
	int	in_and_out_file;

	in_and_out_file = NOFILE;
	if (cmd_list->redir != NULL)
	{
//		fprintf(stderr, "redir is not NULL\n");
//		fprintf(stderr, "redir type = %d\n", cmd_data->redir->type);
		if (cmd_list->redir->type == REDIR_IN || cmd_list->redir->type == WORD)
		{
			printf("should be input file or no file\n");
			in_and_out_file = INPUT;
		}
		else if (cmd_list->redir->type == REDIR_OUT) // maybe combine my input and output ints with t_type
		{
			printf("should be output file\n");
			in_and_out_file = OUTPUT;
		}
	}
	else
	{
		printf("should be no file\n");
		in_and_out_file = NOFILE;
	}
	return (in_and_out_file);
}

// void	run_pipeline(t_cmd *cmd_list, char *env[]) // working
// {
// 	int		pipe_fd[2];
// 	int		prev_pipe_fd[2] = {-1, -1};
// 	pid_t	process_id;
// 	int		in_and_out_file;
// 	size_t	cmd_count;
// 	int		input_fd;
// 	int		output_fd;
//
// 	cmd_count = 0;
// 	while (cmd_list != NULL)
// 	{
// 		if (cmd_list->next != NULL)
// 		{
// 			if (pipe(pipe_fd) == -1)
// 				print_error_msg_and_exit(ERR_PIPE);
// 		}
// 		process_id = fork();
// 		if (process_id < 0)
// 			print_error_msg_and_exit(ERR_FORK);
// 		if (process_id == 0) // Child process
// 		{
// 			in_and_out_file = determine_filetype(cmd_list);
// 			// Handle file redirections first
// 			if (in_and_out_file == INPUT)
// 			{
// 				input_fd = open_input_or_output_file(cmd_list->redir->file_name, INPUT);
// 				if (input_fd == -1)
// 					print_error_msg_and_exit(ERR_FILE);
// 				dup2(input_fd, STDIN_FILENO);
// 				close(input_fd);
// 			}
// 			else if (in_and_out_file == OUTPUT)
// 			{
// 				output_fd = open_input_or_output_file(cmd_list->redir->file_name, OUTPUT);
// 				if (output_fd == -1)
// 					print_error_msg_and_exit(ERR_FILE);
// 				dup2(output_fd, STDOUT_FILENO);
// 				close(output_fd);
// 			}
// 			// Handle pipe redirections
// 			if (cmd_count > 0 && in_and_out_file != INPUT)
// 			{
// 				dup2(prev_pipe_fd[0], STDIN_FILENO);
// 				close(prev_pipe_fd[0]);
// 			}
// 			if (cmd_list->next != NULL && in_and_out_file != OUTPUT)
// 			{
// 				dup2(pipe_fd[1], STDOUT_FILENO);
// 				close(pipe_fd[0]);  // Close read end in child
// 				close(pipe_fd[1]);  // Close after dup2
// 			}
//
// 			// Run the command
// 			if (cmd_list->builtin)
// 				run_builtin(cmd_list, env);
// 			else
// 				run_cmd(cmd_list, env);
// 			exit(EXIT_SUCCESS);
// 		}
// 		else // Parent process
// 		{
// 			// Close write end of current pipe immediately
// 			if (cmd_list->next != NULL)
// 				close(pipe_fd[1]);
//
// 			// Close previous pipe read end
// 			if (prev_pipe_fd[0] != -1)
// 				close(prev_pipe_fd[0]);
//
// 			// Save new read end for next command
// 			if (cmd_list->next != NULL)
// 				prev_pipe_fd[0] = pipe_fd[0];
//
// 			handle_parent_process(process_id, cmd_list);
// 		}
// 		cmd_list = cmd_list->next;
// 		cmd_count++;
// 	}
// }

void prepare_parent_process(t_cmd *cmd, pid_t process_id, int prev_pipe_fd[2], int pipe_fd[2])
{
	if (cmd->next != NULL)
		close(pipe_fd[1]);

	if (prev_pipe_fd[0] != -1)
		close(prev_pipe_fd[0]);

	if (cmd->next != NULL)
		prev_pipe_fd[0] = pipe_fd[0];

	handle_parent_process(process_id, cmd);
}

static void	setup_pipe(t_cmd *cmd, int pipe_fd[2])
{
	if (cmd->next != NULL)
	{
		if (pipe(pipe_fd) == -1)
			print_error_msg_and_exit(ERR_PIPE);
	}
}

static void	redirect_input(t_cmd *cmd)
{
	int	input_fd;

	input_fd = open_input_or_output_file(cmd->redir->file_name, INPUT);
	if (input_fd == -1)
		print_error_msg_and_exit(ERR_FILE);
	dup2(input_fd, STDIN_FILENO);
	close(input_fd);
}

static void	redirect_output(t_cmd *cmd)
{
	int	output_fd;

	output_fd = open_input_or_output_file(cmd->redir->file_name, OUTPUT);
	if (output_fd == -1)
		print_error_msg_and_exit(ERR_FILE);
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);
}

void handle_file_redirections(t_cmd *cmd)
{
	int	in_and_out_file;

	in_and_out_file = determine_filetype(cmd);
	if (in_and_out_file == INPUT)
		redirect_input(cmd);
	else if (in_and_out_file == OUTPUT)
		redirect_output(cmd);
}

void handle_pipe_redirections(t_cmd *cmd, int prev_pipe_fd[2], int pipe_fd[2], size_t cmd_count)
{
	int in_and_out_file;

	in_and_out_file = determine_filetype(cmd);
	if (cmd_count > 0 && in_and_out_file != INPUT)
	{
		dup2(prev_pipe_fd[0], STDIN_FILENO);
		close(prev_pipe_fd[0]);
	}
	if (cmd->next != NULL && in_and_out_file != OUTPUT)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);  // Close read end in child
		close(pipe_fd[1]);  // Close after dup2
	}
}

void handle_child_process(t_cmd *cmd, char *env[], int prev_pipe_fd[2], int pipe_fd[2], size_t cmd_count)
{
	handle_file_redirections(cmd);
	handle_pipe_redirections(cmd, prev_pipe_fd, pipe_fd, cmd_count);
	run_builtin_or_execute(cmd, env);
	exit(EXIT_SUCCESS);
}

void run_pipeline(t_cmd *cmd_list, char *env[])
{
	int	pipe_fd[2];
	int	prev_pipe_fd[2] = {-1, -1};
	pid_t process_id;
	size_t cmd_count = 0;

	while (cmd_list != NULL)
	{
		setup_pipe(cmd_list, pipe_fd);
		process_id = fork();
		if (process_id < 0)
			print_error_msg_and_exit(ERR_FORK);
		if (process_id == 0) // Child process
			handle_child_process(cmd_list, env, prev_pipe_fd, pipe_fd, cmd_count);
		else // Parent process
			prepare_parent_process(cmd_list, process_id, prev_pipe_fd, pipe_fd);
		cmd_list = cmd_list->next;
		cmd_count++;
	}

}
void	run_process(t_cmd *cmd_list, char *env[])
{
	size_t	cmd_count;

	cmd_count = 0;
	if (cmd_list == NULL)
	{
		printf("No commands to execute\n");
		return ;
	}
	cmd_count = get_cmd_data_list_size(cmd_list);
	if (cmd_count == 1)
		run_builtin_or_execute(cmd_list, env); // without pipe_fd and inandoutfile and run cmd straigth
	else if (cmd_count >= 2) // change to else if
	{
		printf("run %ld cmds\n", cmd_count);
		run_pipeline(cmd_list, env);
	}
}

void	run_cmd(t_cmd *cmd_data, char *env[])
{
	char	*full_cmd;
	char	**split_cmd;
	char	*exec_path;
//	fprintf(stderr, "cmd_data->cmd: %s\n", cmd_data->cmd);
	full_cmd = combine_command_and_args(cmd_data->cmd, cmd_data->args); // temporary
	// fprintf(stderr, "full_cmd after combine call: %s\n", full_cmd);
	exec_path = get_exec_path(cmd_data->cmd, env);
	split_cmd = parse_command_with_quotes(full_cmd);
//	 fprintf(stderr, "Executable Path: %s\n", exec_path);

	// fprintf(stderr, "Command arguments:\n");
	// for (int i = 0; split_cmd[i]; i++)
	// {
	// 	fprintf(stderr, "split_cmd[%d]: %s\n", i, split_cmd[i]);
	// }
	// free(cmd);
	if (execve(exec_path, split_cmd, env) == -1)
	{
		fprintf(stderr, "Error executing %s: %s\n", exec_path, strerror(errno)); // maybe its possible to return with my error function
		free(exec_path);
		ft_free_array(split_cmd);
		exit(EXIT_FAILURE);
	}
	free(exec_path);
	ft_free_array(split_cmd);
	print_error_msg_and_exit(ERR_UNKNOWN);
}

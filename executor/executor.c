
#include "../lib/minishell.h"

void close_unused_pipes(int pipe_fd[2], int prev_pipe_fd[2])
{
	// Close the current pipe if it was created
	if (pipe_fd != NULL)
	{
		close(pipe_fd[0]); // Close the read end of the current pipe
		close(pipe_fd[1]); // Close the write end of the current pipe
	}

	// Close the previous pipe if it was created
	if (prev_pipe_fd != NULL)
	{
		close(prev_pipe_fd[0]); // Close the read end of the previous pipe
		close(prev_pipe_fd[1]); // Close the write end of the previous pipe
	}
}

//void	run_process(t_cmd *cmd_data, char *env[]) // rewrite to determine if pipes are needed if not just run the command straigth
//{
//	int		in_and_out_file;
//	int		pipe_fd[2]; // change to count of all cmds instead of 2
//	pid_t	process_id;
//
//	if (cmd_data->redir != NULL)
//	{
////		fprintf(stderr, "redir is not NULL\n");
////		fprintf(stderr, "redir type = %d\n", cmd_data->redir->type);
//		if (cmd_data->redir->type == REDIR_IN || cmd_data->redir->type == WORD)
//			in_and_out_file = INPUT;
//		else if (cmd_data->redir->type == REDIR_OUT) // maybe combine my input and output ints with t_type
//			in_and_out_file = OUTPUT;
//	}
//	else
//	{
//		fprintf(stderr, "should be no file\n");
//		in_and_out_file = NOFILE;
//	}
////	 in_and_out_file = cmd_data->redir->type; // currenty this would be 87 everytime when a file exists
////	 fprintf(stderr, "in_and_out_file %d\n", in_and_out_file);
//	if (pipe(pipe_fd) == -1)
//		print_error_msg_and_exit(ERR_PIPE);
//	process_id = fork();
//	if (process_id < 0)
//	{
//		free_cmd_data(cmd_data);
//		print_error_msg_and_exit(ERR_FORK);
//	}
//
//	// In the child process
//	if (process_id == 0)
//	{
//		run_builtin_or_execute(cmd_data, env, pipe_fd, in_and_out_file);
//	}
//	else
//	{
//		// In the parent process
//		handle_parent_process(process_id, cmd_data);
//	}
//}
int		determine_filetype(t_cmd *cmd_list)
{
	int	in_and_out_file;

	if (cmd_list->redir != NULL)
	{
//		fprintf(stderr, "redir is not NULL\n");
//		fprintf(stderr, "redir type = %d\n", cmd_data->redir->type);
		if (cmd_list->redir->type == REDIR_IN || cmd_list->redir->type == WORD)
		{
			printf("should be input file\n");
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

void	run_pipeline(t_cmd *cmd_list, char *env[])
{
	int		pipe_fd[2];
	int		prev_pipe_fd[2] = {-1, -1};
	pid_t	process_id;
	int		in_and_out_file;
	size_t	cmd_count;
	int		input_fd;
	int		output_fd;

	cmd_count = 0;
	while (cmd_list != NULL)
	{
		if (cmd_list->next != NULL)
		{
			if (pipe(pipe_fd) == -1)
				print_error_msg_and_exit(ERR_PIPE);
		}
		process_id = fork();
		if (process_id < 0)
			print_error_msg_and_exit(ERR_FORK);
		if (process_id == 0) // Child process
		{
			in_and_out_file = determine_filetype(cmd_list);
			// Handle file redirections first
			if (in_and_out_file == INPUT)
			{
				input_fd = open_input_or_output_file(cmd_list->redir->file_name, INPUT);
				if (input_fd == -1)
					print_error_msg_and_exit(ERR_FILE);
				dup2(input_fd, STDIN_FILENO);
				close(input_fd);
			}
			else if (in_and_out_file == OUTPUT)
			{
				output_fd = open_input_or_output_file(cmd_list->redir->file_name, OUTPUT);
				if (output_fd == -1)
					print_error_msg_and_exit(ERR_FILE);
				dup2(output_fd, STDOUT_FILENO);
				close(output_fd);
			}
			// Handle pipe redirections
			if (cmd_count > 0 && in_and_out_file != INPUT)
			{
				dup2(prev_pipe_fd[0], STDIN_FILENO);
				close(prev_pipe_fd[0]);
			}
			if (cmd_list->next != NULL && in_and_out_file != OUTPUT)
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[0]);  // Close read end in child
				close(pipe_fd[1]);  // Close after dup2
			}

			// Run the command
			if (cmd_list->builtin)
				run_builtin(cmd_list, env);
			else
				run_cmd(cmd_list, env);
			exit(EXIT_SUCCESS);
		}
		else // Parent process
		{
			// Close write end of current pipe immediately
			if (cmd_list->next != NULL)
				close(pipe_fd[1]);

			// Close previous pipe read end
			if (prev_pipe_fd[0] != -1)
				close(prev_pipe_fd[0]);

			// Save new read end for next command
			if (cmd_list->next != NULL)
				prev_pipe_fd[0] = pipe_fd[0];

			handle_parent_process(process_id, cmd_list);
		}
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
	if (cmd_count >= 2) // change to else if later
	{
		printf("run at least 2 cmds\n");
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


#include "../lib/minishell.h"

void	handle_file_redirections(t_cmd *cmd)
{
	t_redir	*current_redir;
	int		input_fd;
	int		output_fd;

	fprintf(stderr, "DEBUG: Handling file redirections for command: %s\n", cmd->cmd);
	current_redir = cmd->redir;
	while (current_redir != NULL)
	{
		fprintf(stderr, "DEBUG: Redirection type: %d, File: %s\n", current_redir->type, current_redir->file_name);
		if (current_redir->type == REDIR_IN || current_redir->type == WORD)
		{
			input_fd = open_input_or_output_file(current_redir->file_name, INPUT);
			if (input_fd == -1)
				print_error_msg_and_exit(ERR_FILE);
			fprintf(stderr, "DEBUG: Setting up input redirection, fd: %d\n", input_fd);
			if (dup2(input_fd, STDIN_FILENO) == -1)
				print_error_msg_and_exit(ERR_DUP2);
			close(input_fd);
		}
		else if (current_redir->type == REDIR_OUT)
		{
			output_fd = open_input_or_output_file(current_redir->file_name, OUTPUT);
			if (output_fd == -1)
				print_error_msg_and_exit(ERR_FILE);
			fprintf(stderr, "DEBUG: Setting up output redirection, fd: %d\n", output_fd);
			if (dup2(output_fd, STDOUT_FILENO) == -1)
				print_error_msg_and_exit(ERR_DUP2);
			close(output_fd);
		}
		current_redir = current_redir->next;
	}
}

void	handle_pipe_redirections(t_cmd *cmd, int prev_pipe_fd[2],
								int pipe_fd[2], size_t cmd_count)
{
	fprintf(stderr, "DEBUG: Handling pipe redirections for command %zu\n", cmd_count);
	fprintf(stderr, "DEBUG: Command: %s\n", cmd->cmd);

	if (cmd_count > 0)
	{
		fprintf(stderr, "DEBUG: Setting up input from previous pipe\n");
		dup2(prev_pipe_fd[0], STDIN_FILENO);
		close(prev_pipe_fd[0]); // close read_of prev pipe
		if (prev_pipe_fd[1] != -1)
			close(prev_pipe_fd[1]); // close writ_of prev pipe
	}
	if (cmd->next != NULL) // when not last cmd
	{
		fprintf(stderr, "DEBUG: Setting up output to next pipe\n");
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
}

static void	handle_first_command(t_cmd *cmd, int pipe_fd[2])
{
	fprintf(stderr, "DEBUG: First command setup\n");
	if (cmd->redir)
	{
		handle_file_redirections(cmd);
		fprintf(stderr, "DEBUG: After file redir - stdin: %d, stdout: %d\n",
				fcntl(STDIN_FILENO, F_GETFD),
				fcntl(STDOUT_FILENO, F_GETFD));
	}
	if (cmd->next && pipe_fd[1] != -1)
	{
		fprintf(stderr, "DEBUG: Setting up pipe output. pipe_fd[1]: %d\n", pipe_fd[1]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
}

// Helper function to handle middle command setup
static void	handle_middle_command(t_cmd *cmd, int prev_pipe_fd[2], int pipe_fd[2], size_t cmd_count)
{
	fprintf(stderr, "DEBUG: Middle command setup\n");
	handle_pipe_redirections(cmd, prev_pipe_fd, pipe_fd, cmd_count);
	if (cmd->redir)
		handle_file_redirections(cmd);
}

// Helper function to handle last command setup
static void	handle_last_command(t_cmd *cmd, int prev_pipe_fd[2])
{
	fprintf(stderr, "DEBUG: Last command setup\n");
	if (prev_pipe_fd[0] != -1)
	{
		fprintf(stderr, "DEBUG: Setting up pipe input. prev_pipe_fd[0]: %d\n", prev_pipe_fd[0]);
		dup2(prev_pipe_fd[0], STDIN_FILENO);
		close(prev_pipe_fd[0]);
	}
	if (prev_pipe_fd[1] != -1)
		close(prev_pipe_fd[1]);

	if (cmd->redir)
		handle_file_redirections(cmd);
}

// Helper function to execute the command
static void	execute_command(t_cmd *cmd, char *env[])
{
	if (cmd->builtin)
		run_builtin(cmd, env);
	else
		run_cmd(cmd, env);
	exit(EXIT_SUCCESS);
}

// Main child process handler
void	handle_child_process(t_cmd *cmd, char *env[], int prev_pipe_fd[2], int pipe_fd[2], size_t cmd_count)
{
	fprintf(stderr, "DEBUG: Child process for command: %s\n", cmd->cmd);
	if (cmd_count == 0)
		handle_first_command(cmd, pipe_fd);
	else if (cmd->next == NULL)
		handle_last_command(cmd, prev_pipe_fd);
	else
		handle_middle_command(cmd, prev_pipe_fd, pipe_fd, cmd_count);
	print_fd_debug("DEBUG: Final FDs before exec");
	execute_command(cmd, env);
}

void	run_pipeline(t_cmd *cmd_list, char *env[])
{
	int		pipe_fd[2] = {-1, -1};
	int		prev_pipe_fd[2] = {-1, -1};
	pid_t	process_id;
	size_t	cmd_count;
	int		original_stdout;

	// Save original stdout
	original_stdout = dup(STDOUT_FILENO);
	cmd_count = 0;
	fprintf(stderr, "DEBUG: Original stdout: %d\n", original_stdout);

	while (cmd_list != NULL)
	{
		fprintf(stderr, "DEBUG: Processing command: %s\n", cmd_list->cmd);

		// Only create new pipe if there's a next command
		if (cmd_list->next != NULL)
		{
			if (pipe(pipe_fd) == -1)
				print_error_msg_and_exit(ERR_PIPE);
			fprintf(stderr, "DEBUG: Created new pipe: [%d, %d]\n", pipe_fd[0], pipe_fd[1]);
		}
		else
		{
			pipe_fd[0] = -1;
			pipe_fd[1] = -1;
			fprintf(stderr, "DEBUG: Last command, no new pipe created\n");
		}

		process_id = fork();
		if (process_id < 0)
			print_error_msg_and_exit(ERR_FORK);

		if (process_id == 0) // Child process
		{
			if (original_stdout != -1)
				close(original_stdout);
			handle_child_process(cmd_list, env, prev_pipe_fd, pipe_fd, cmd_count);
		}
		else // Parent process
		{
			fprintf(stderr, "DEBUG: Parent process\n");
			// Close previous pipe fds in parent
			if (prev_pipe_fd[0] != -1)
			{
				fprintf(stderr, "DEBUG: Closing prev_pipe_fd[0]: %d\n", prev_pipe_fd[0]);
				close(prev_pipe_fd[0]);
			}
			if (prev_pipe_fd[1] != -1)
			{
				fprintf(stderr, "DEBUG: Closing prev_pipe_fd[1]: %d\n", prev_pipe_fd[1]);
				close(prev_pipe_fd[1]);
			}

			// Save current pipe as previous for next iteration
			prev_pipe_fd[0] = pipe_fd[0];
			prev_pipe_fd[1] = pipe_fd[1];

//			waitpid(process_id, NULL, 0);
			handle_parent_process(process_id, cmd_list);
		}
		cmd_list = cmd_list->next;
		cmd_count++;
	}

	// Close any remaining pipe fds
	if (prev_pipe_fd[0] != -1)
		close(prev_pipe_fd[0]);
	if (prev_pipe_fd[1] != -1)
		close(prev_pipe_fd[1]);

	if (original_stdout != -1)
		close(original_stdout);
}

void	run_process(t_cmd *cmd_list, char *env[])
{
	size_t	cmd_count;

	cmd_count = 0;
	if (cmd_list == NULL)
	{
		printf("No commands to execute\n"); //debug print
		return ;
	}
	cmd_count = get_cmd_data_list_size(cmd_list);
	if (cmd_count == 1)
		run_builtin_or_execute(cmd_list, env); // without pipe_fd and inandoutfile and run cmd straigth
	else if (cmd_count >= 2) // change to else if
	{
		printf("run %ld cmds\n", cmd_count); //debug print
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

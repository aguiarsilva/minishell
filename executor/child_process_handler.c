
#include "../lib/minishell.h"

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

// Main child process handler
static void	handle_child_process(t_cmd *cmd, char *env[], int prev_pipe_fd[2], int pipe_fd[2], size_t cmd_count)
{
	fprintf(stderr, "DEBUG: Child process for command: %s\n", cmd->cmd);
	if (cmd_count == 0)
		handle_first_command(cmd, pipe_fd);
	else if (cmd->next == NULL)
		handle_last_command(cmd, prev_pipe_fd);
	else
		handle_middle_command(cmd, prev_pipe_fd, pipe_fd, cmd_count);
	print_fd_debug("DEBUG: Final FDs before exec");
	run_builtin_or_execute(cmd, env);
}

// Create child process
pid_t	create_child_process(t_cmd *cmd, char *env[], int prev_pipe_fd[2], int pipe_fd[2], int original_stdout)
{
	pid_t	process_id;
	size_t	cmd_count;
	process_id = fork();
	cmd_count = get_cmd_data_list_size(cmd);
	if (process_id < 0)
		print_error_msg_and_exit(ERR_FORK);
	if (process_id == 0)
	{
		if (original_stdout != -1)
			close(original_stdout);
		handle_child_process(cmd, env, prev_pipe_fd, pipe_fd, cmd_count);
	}
	return (process_id);
}

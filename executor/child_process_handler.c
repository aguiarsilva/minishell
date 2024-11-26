// too many args 
#include "../lib/minishell.h"

static void	handle_first_command(t_cmd *cmd, int pipe_fd[2])
{
	fprintf(stderr, "DEBUG: First command setup\n");
	handle_file_redirections(cmd);
	if (cmd->next && pipe_fd[1] != -1)
	{
		fprintf(stderr, "DEBUG: Setting up pipe output for first command\n");
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
}

static void	handle_middle_command(t_cmd *cmd, int prev_pipe_fd[2],
									int pipe_fd[2], size_t cmd_count)
{
	fprintf(stderr, "DEBUG: Middle command setup\n");
	handle_pipe_redirections(cmd, prev_pipe_fd, pipe_fd, cmd_count);
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
	handle_file_redirections(cmd);
}

// Main child process handler
void	handle_child_process(t_cmd *cmd, t_env **env_lst,
							int prev_pipe_fd[2], int pipe_fd[2],
							size_t cmd_position)
{
	fprintf(stderr, "DEBUG: Child process for command: %s\n", cmd->cmd);

	if (cmd_position == 0)
		handle_first_command(cmd, pipe_fd);
	else if (!cmd->next)
		handle_last_command(cmd, prev_pipe_fd);
	else
		handle_middle_command(cmd, prev_pipe_fd, pipe_fd, cmd_position);
	print_fd_debug("DEBUG: Final FDs before exec");
	run_builtin_or_execute(cmd, env_lst);
}


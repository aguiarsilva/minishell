
#include "../lib/minishell.h"

static void handle_first_command(t_cmd *cmd, int pipe_fd[2])
{
	fprintf(stderr, "DEBUG: First command setup\n");

	// Handle input redirections if present
	if (cmd->redir)
		handle_input_redirections(cmd);

	// Set up pipe output if there's a next command
	if (cmd->next && pipe_fd[1] != -1)
	{
		fprintf(stderr, "DEBUG: Setting up pipe output for first command\n");
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
}

// Helper function to handle middle command setup
static void	handle_middle_command(t_cmd *cmd, int prev_pipe_fd[2],
									int pipe_fd[2], size_t cmd_count)
{
	fprintf(stderr, "DEBUG: Middle command setup\n");
	handle_pipe_redirections(cmd, prev_pipe_fd, pipe_fd, cmd_count);

	// Middle commands should not handle file redirections
	// They should only use pipe redirections
}

// Helper function to handle last command setup
static void	handle_last_command(t_cmd *cmd, int prev_pipe_fd[2])
{
	fprintf(stderr, "DEBUG: Last command setup\n");

	// Handle input from previous pipe
	if (prev_pipe_fd[0] != -1)
	{
		fprintf(stderr, "DEBUG: Setting up pipe input. prev_pipe_fd[0]: %d\n", prev_pipe_fd[0]);
		dup2(prev_pipe_fd[0], STDIN_FILENO);
		close(prev_pipe_fd[0]);
	}
	if (prev_pipe_fd[1] != -1)
		close(prev_pipe_fd[1]);

	// Handle output redirections if any
	if (cmd->redir)
		handle_file_redirections(cmd);
}

// Main child process handler
void	handle_child_process(t_cmd *cmd, char *env[],
							int prev_pipe_fd[2], int pipe_fd[2], size_t cmd_position)
{
	fprintf(stderr, "DEBUG: Child process for command: %s\n", cmd->cmd);

	// Handle command based on its position in the pipeline
	if (cmd_position == 0)
		handle_first_command(cmd, pipe_fd);
	else if (!cmd->next)
		handle_last_command(cmd, prev_pipe_fd);
	else
		handle_middle_command(cmd, prev_pipe_fd, pipe_fd, cmd_position);
	print_fd_debug("DEBUG: Final FDs before exec");
	run_builtin_or_execute(cmd, env);
}


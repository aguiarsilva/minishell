
#include "../lib/minishell.h"

// Handle parent process tasks
void	handle_parent_exit(pid_t process_id, t_cmd *cmd_data)
{
	// Free the command data in the parent process
	free(cmd_data); // should only free when minishell is exited?

	// Wait for the child process and check its status
	check_child_status(process_id);
}

void	handle_parent_pipes_and_process(pid_t process_id, t_cmd *cmd, int prev_pipe_fd[2], int pipe_fd[2])
{
	fprintf(stderr, "DEBUG: Parent process\n");
	close_pipe_fds(prev_pipe_fd);
	update_prev_pipe_fds(prev_pipe_fd, pipe_fd);
	handle_parent_exit(process_id, cmd);
}
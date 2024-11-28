
#include "../lib/minishell.h"

// Initialize pipe file descriptors
void	init_pipe_fds(int pipe_fd[2], int prev_pipe_fd[2])
{
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	prev_pipe_fd[0] = -1;
	prev_pipe_fd[1] = -1;
}

// Close pipe file descriptors
void	close_pipe_fds(int pipe_fd[2])
{
	if (pipe_fd[0] != -1)
	{
//		 fprintf(stderr, "DEBUG: Closing pipe_fd[0]: %d\n", pipe_fd[0]);
		close(pipe_fd[0]);
	}
	if (pipe_fd[1] != -1)
	{
//		 fprintf(stderr, "DEBUG: Closing pipe_fd[1]: %d\n", pipe_fd[1]);
		close(pipe_fd[1]);
	}
}

// Update previous pipe file descriptors
void	update_prev_pipe_fds(int prev_pipe_fd[2], int pipe_fd[2])
{
	prev_pipe_fd[0] = pipe_fd[0];
	prev_pipe_fd[1] = pipe_fd[1];
}


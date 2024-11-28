
#include "../lib/minishell.h"

void	handle_file_redirections(t_cmd *cmd)
{
	int		output_fd;
	int		input_fd;
	t_redir	*cur_redir;

	output_fd = -1;
	input_fd = -1;
	if (!cmd->redir)
		return ;
	cur_redir = cmd->redir;
	while (cur_redir != NULL)
	{
		handle_input_redirection(cur_redir, &input_fd);
		handle_output_redirection(cur_redir, &output_fd);
		cur_redir = cur_redir->next;
	}
	apply_input_redirection(input_fd);
	apply_output_redirection(output_fd);
}

void	handle_pipe_redirections(t_cmd *cmd, int prev_pipe_fd[2],
								int pipe_fd[2], size_t cmd_count)
{
//	 fprintf(stderr, "DEBUG: Handling pipe redirections for command %zu\n", cmd_count);
//	 fprintf(stderr, "DEBUG: Command: %s\n", cmd->cmd);

	if (cmd_count > 0)
	{
//		fprintf(stderr, "DEBUG: Setting up input from previous pipe\n");
		dup2(prev_pipe_fd[0], STDIN_FILENO);
		close(prev_pipe_fd[0]);
		if (prev_pipe_fd[1] != -1)
			close(prev_pipe_fd[1]);
	}
	if (cmd->next != NULL)
	{
//		fprintf(stderr, "DEBUG: Setting up output to next pipe\n");
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
}

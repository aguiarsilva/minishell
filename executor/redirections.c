
#include "../lib/minishell.h"

void	handle_file_redirections(t_cmd *cmd)
{
	if (!cmd->redir)
		return ;

	if (cmd->redir->type == REDIR_IN)
		handle_input_redirections(cmd);
	else if (cmd->redir->type == REDIR_OUT || cmd->redir->type == APPEND)
		handle_output_redirections(cmd);
}

void	handle_input_redirections(t_cmd *cmd)
{
	t_redir	*cur_redir;
	int		fd;

	// fprintf(stderr, "DEBUG: Handling input redirections for command: %s\n", cmd->cmd);
	cur_redir = cmd->redir;
	while (cur_redir != NULL)
	{
		// fprintf(stderr, "DEBUG: Redirection type: %d, File: %s\n",
		// 	cur_redir->type, cur_redir->file_name);

		if (cur_redir->type == REDIR_IN)
		{
			fd = open(cur_redir->file_name, O_RDONLY);
			if (fd == -1)
				print_error_msg_and_exit(ERR_FILE);

			if (dup2(fd, STDIN_FILENO) == -1)
			{
				close(fd);
				print_error_msg_and_exit(ERR_DUP2);
			}
			close(fd);
		}
		cur_redir = cur_redir->next;
	}
}

void	handle_output_redirections(t_cmd *cmd)
{
	t_redir	*cur_redir;
	int		fd;

	// fprintf(stderr, "DEBUG: Handling output redirections for command: %s\n", cmd->cmd);
	cur_redir = cmd->redir;
	while (cur_redir != NULL)
	{
		// fprintf(stderr, "DEBUG: Redirection type: %d, File: %s\n",
			// cur_redir->type, cur_redir->file_name);
		if (cur_redir->type == REDIR_OUT)
		{
			fd = open(cur_redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				print_error_msg_and_exit(ERR_FILE);
		}
		else if (cur_redir->type == APPEND)
		{
			fd = open(cur_redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				print_error_msg_and_exit(ERR_FILE);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			close(fd);
			print_error_msg_and_exit(ERR_DUP2);
		}
		close(fd);
		cur_redir = cur_redir->next;
	}
}

void	handle_pipe_redirections(t_cmd *cmd, int prev_pipe_fd[2],
								int pipe_fd[2], size_t cmd_count)
{
	// fprintf(stderr, "DEBUG: Handling pipe redirections for command %zu\n", cmd_count);
	// fprintf(stderr, "DEBUG: Command: %s\n", cmd->cmd);

	if (cmd_count > 0)
	{
		// fprintf(stderr, "DEBUG: Setting up input from previous pipe\n");
		dup2(prev_pipe_fd[0], STDIN_FILENO);
		close(prev_pipe_fd[0]);
		if (prev_pipe_fd[1] != -1)
			close(prev_pipe_fd[1]);
	}
	if (cmd->next != NULL)
	{
		// fprintf(stderr, "DEBUG: Setting up output to next pipe\n");
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
}

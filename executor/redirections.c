
#include "../lib/minishell.h"

static int	open_input_or_output_file(char *filename, int in_or_out)
{
	int	ret;

	ret = 0;
	if (in_or_out == INPUT)
		ret = open(filename, O_RDONLY, 0666);
	else if (in_or_out == OUTPUT)
		ret = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		print_error_msg_and_exit(ERR_IMPOSSIBLE);
	if (ret == -1)
		print_error_open_file_and_exit(filename, errno); // not sure if this is enough or a custom function is needed
	return (ret);
}

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

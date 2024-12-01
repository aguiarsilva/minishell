/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:42:29 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/11/28 15:42:29 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	apply_input_redirection(int input_fd)
{
	if (input_fd == -1)
		return ;
	if (dup2(input_fd, STDIN_FILENO) == -1)
	{
		close(input_fd);
		print_error_msg_and_exit(ERR_DUP2);
	}
	close(input_fd);
}

void	apply_output_redirection(int output_fd)
{
	if (output_fd == -1)
		return ;
	if (dup2(output_fd, STDOUT_FILENO) == -1)
	{
		close(output_fd);
		print_error_msg_and_exit(ERR_DUP2);
	}
	close(output_fd);
}

void	handle_input_redirection(t_redir *cur_redir, int *input_fd)
{
	if (cur_redir->type == REDIR_IN)
	{
		if (*input_fd != -1)
			close(*input_fd);
		*input_fd = open_input_file(cur_redir->file_name);
	}
}

void	handle_output_redirection(t_redir *cur_redir, int *output_fd)
{
	if (cur_redir->type == REDIR_OUT)
	{
		if (*output_fd != -1)
			close(*output_fd);
		*output_fd = open_output_file(cur_redir->file_name, O_TRUNC);
	}
	else if (cur_redir->type == APPEND)
	{
		if (*output_fd != -1)
			close(*output_fd);
		*output_fd = open_output_file(cur_redir->file_name, O_APPEND);
	}
}

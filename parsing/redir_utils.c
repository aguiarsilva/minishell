/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:39:47 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/11/25 22:39:47 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

t_redir	*get_last_redirection_node(t_redir *redir_head)
{
	t_redir	*last_redir_node;

	last_redir_node = redir_head;
	while (last_redir_node && last_redir_node->next != NULL)
		last_redir_node = last_redir_node->next;
	return (last_redir_node);
}

bool	is_filename(const char *str)
{
	const char	*dot_position;
	const char	*file_extension;

	dot_position = ft_strrchr(str, '.');
	if (dot_position && dot_position != str && *(dot_position + 1) != '\0')
	{
		file_extension = dot_position + 1;
		while (*file_extension != '\0')
		{
			if (!ft_isalnum(*file_extension))
				return (false);
			file_extension++;
		}
		return (true);
	}
	return (false);
}

bool	is_file_without_extension(t_token *prev_token, t_token *cur_token)
{
	if (!prev_token || !cur_token)
		return (false);
	if ((prev_token->type == REDIR_OUT
			|| prev_token->type == REDIR_IN
			|| prev_token->type == APPEND)
		&& cur_token->type == WORD)
		return (true);
	return (false);
}

int	determine_redirection_type(int filetype)
{
	if (filetype == INPUT || filetype == HEREDOC_INPUT)
		return (REDIR_IN);
	else if (filetype == OUTPUT)
		return (REDIR_OUT);
	else if (filetype == APPEND_OUTPUT)
		return (APPEND);
	else
		return (WORD);
}

int	determine_file_type(t_token *cur_token)
{
	int	file_type;

	file_type = -1;
	if (get_token_type(cur_token->val) == REDIR_IN)
		file_type = INPUT;
	else if (get_token_type(cur_token->val) == HEREDOC)
		file_type = HEREDOC_INPUT;
	else if (get_token_type(cur_token->val) == APPEND)
		file_type = APPEND_OUTPUT;
	else if (get_token_type(cur_token->val) == REDIR_OUT)
		file_type = OUTPUT;
	return (file_type);
}

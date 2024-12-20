/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:52:14 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/12/01 15:02:56 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static t_redir	*init_redirection_node(t_token *token_node, int filetype)
{
	t_redir	*new_redir;
	char	*filename;

	new_redir = malloc(sizeof(t_redir));
	if (new_redir == NULL)
	{
		printf("Memory allocation failed for redirection node\n");
		return (NULL);
	}
	filename = token_node->val;
	new_redir->file_name = ft_strdup(filename);
	if (new_redir->file_name == NULL)
	{
		printf("Memory allocation failed for file_name\n");
		return (NULL);
	}
	new_redir->type = determine_redirection_type(filetype);
	new_redir->next = NULL;
	return (new_redir);
}

static t_redir	*create_redir_struct(t_redir **redir_head,
								t_token *token_node, int filetype)
{
	t_redir	*new_redir;
	t_redir	*last_redir;

	new_redir = init_redirection_node(token_node, filetype);
	if (new_redir == NULL)
		return (NULL);
	if (*redir_head == NULL)
		*redir_head = new_redir;
	else
	{
		last_redir = get_last_redirection_node(*redir_head);
		last_redir->next = new_redir;
	}
	return (*redir_head);
}

void	add_to_redir_lst(t_token *cur_token, t_redir **redir_lst,
						int file_type, t_token *prev_token)
{
	if (is_filename(cur_token->val) || cur_token->eof_flag
		||is_file_without_extension(prev_token, cur_token))
	{
		if (cur_token->eof_flag)
			create_redir_struct(redir_lst, prev_token, file_type);
		else
			create_redir_struct(redir_lst, cur_token, file_type);
	}
}

void	append_redir_node(t_redir **redir_lst, t_redir **last_redir,
						t_redir *new_redir)
{
	if (new_redir)
	{
		if (*redir_lst == NULL)
		{
			*redir_lst = new_redir;
			*last_redir = *redir_lst;
		}
		else
		{
			(*last_redir)->next = new_redir;
			*last_redir = new_redir;
		}
	}
}

t_redir	*check_if_token_need_redir(t_token **token_list,
			t_token *cur_token, t_redir *cur_redir)
{
	if (cur_token != NULL)
	{
		*token_list = cur_token->next;
		if (cur_redir)
			return (cur_redir->next);
		else
			return (NULL);
	}
	return (cur_redir);
}

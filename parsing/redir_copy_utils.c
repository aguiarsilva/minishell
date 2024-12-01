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

static t_redir	*copy_redirection_node(t_redir *original_node)
{
	t_redir	*new_node;

	new_node = malloc(sizeof(t_redir));
	if (new_node == NULL)
	{
		printf("Memory allocation failed for redirection node\n");
		return (NULL);
	}
	new_node->file_name = ft_strdup(original_node->file_name);
	if (new_node->file_name == NULL)
	{
		printf("Memory allocation failed for file_name\n");
		free(new_node);
		return (NULL);
	}
	new_node->type = original_node->type;
	new_node->next = NULL;
	return (new_node);
}

static t_redir	*copy_and_insert_redir_node(t_redir *current,
			t_redir **new_list, t_redir **last)
{
	t_redir	*new_node;

	new_node = copy_redirection_node(current);
	if (new_node == NULL)
		return (NULL);
	if (*new_list == NULL)
		*new_list = new_node;
	else
		(*last)->next = new_node;
	*last = new_node;
	return (*new_list);
}

t_redir	*deep_copy_redir_list(t_redir *original)
{
	t_redir	*new_list;
	t_redir	*last;
	t_redir	*current;

	new_list = NULL;
	last = NULL;
	if (original == NULL)
		return (NULL);
	current = original;
	while (current)
	{
		new_list = copy_and_insert_redir_node(current, &new_list, &last);
		if (new_list == NULL)
			return (NULL);
		current = current->next;
	}
	return (new_list);
}

int	create_and_link_cmd(t_token *token_list, t_redir *cur_redir,
			t_cmd **head, t_cmd **tail)
{
	t_redir	*next_redir;

	next_redir = NULL;
	if (cur_redir)
	{
		next_redir = deep_copy_redir_list(cur_redir);
		if (next_redir == NULL)
			return (1);
	}
	if (create_cmd_from_tokens(token_list, next_redir, head, tail))
		return (1);
	return (0);
}

void	advance_lists_after_pipe(t_token **token_list, t_redir **cur_redir)
{
	t_token	*cur_token;

	cur_token = find_next_pipe_symbol(*token_list);
	if (cur_token != NULL && cur_token->type == PIPE)
	{
		*token_list = cur_token->next;
		if (*cur_redir)
			*cur_redir = (*cur_redir)->next;
	}
}

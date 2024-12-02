/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:20:37 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/12/01 19:20:37 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

t_cmd	*create_new_cmd_node(char *token_val, t_redir *redir_list)
{
	t_cmd	*cmd_list_node;

	cmd_list_node = safe_malloc(sizeof(t_cmd));
	if (cmd_list_node == NULL)
		return (NULL);
	cmd_list_node->cmd = ft_strdup(token_val);
	if (cmd_list_node->cmd == NULL)
	{
		free(cmd_list_node);
		return (NULL);
	}
	cmd_list_node->exit_code = 0;
	if (redir_list == NULL)
		cmd_list_node->redir = NULL;
	else
		cmd_list_node->redir = redir_list;
	cmd_list_node->next = NULL;
	cmd_list_node->builtin = check_for_builtin(cmd_list_node->cmd);
	return (cmd_list_node);
}

void	add_new_cmd_to_cmd_lst(t_cmd **head, t_cmd **tail, t_cmd *new_cmd)
{
	if (*head == NULL)
	{
		*head = new_cmd;
		*tail = new_cmd;
	}
	else
	{
		(*tail)->next = new_cmd;
		*tail = new_cmd;
	}
}

bool	is_skippable_token(t_token *prev, t_token *cur)
{
	if (prev == NULL)
		return (false);
	if ((prev->type == APPEND || prev->type == HEREDOC) && cur->type == WORD)
		return (true);
	if (cur->eof_flag == true)
		return (true);
	if (prev->type != REDIR_OUT && prev->type != REDIR_IN)
		return (false);
	if (get_token_type(cur->val) != WORD)
		return (false);
	return (true);
}

bool	is_special_command(char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_strcmp(cmd, ":") == 0)
		return (true);
	if (ft_strcmp(cmd, "!") == 0)
		return (true);
	return (false);
}

size_t	count_arguments(t_token *token_list)
{
	size_t		arg_count;
	t_token		*cur;

	arg_count = 0;
	cur = token_list;
	while (cur != NULL && cur->type != PIPE)
	{
		if (get_token_type(cur->val) == WORD)
			arg_count++;
		cur = cur->next;
	}
	return (arg_count);
}

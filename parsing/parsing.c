/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:52:14 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/12/01 14:55:04 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static int	process_token_to_args(t_cmd *cmd_data, t_token *cur, int *arg_index)
{
	if (get_token_type(cur->val) != WORD)
		return (1);
	cmd_data->args[*arg_index] = ft_strdup(cur->val);
	if (!cmd_data->args[*arg_index])
		return (0);
	(*arg_index)++;
	return (1);
}

static int	fill_arguments(t_cmd *cmd_data, t_token *token_list,
			size_t *arg_count)
{
	int			arg_index;
	t_token		*cur;
	t_token		*prev;

	arg_index = 0;
	cur = token_list;
	prev = NULL;
	cmd_data->args = malloc((*arg_count + 1) * sizeof(char *));
	if (!cmd_data->args)
		return (-1);
	while (cur && cur->type != PIPE)
	{
		if (is_skippable_token(prev, cur))
		{
			prev = cur;
			cur = cur->next;
			continue ;
		}
		if (!process_token_to_args(cmd_data, cur, &arg_index))
			return (cleanup_args(cmd_data->args, arg_index), -1);
		prev = cur;
		cur = cur->next;
	}
	cmd_data->args[arg_index] = NULL;
	return (0);
}

t_token	*find_next_pipe_symbol(t_token *token_list)
{
	t_token	*cur;

	cur = token_list->next;
	while (cur != NULL && cur->type != PIPE)
		cur = cur->next;
	return (cur);
}

t_cmd	*create_cmd_from_tokens(t_token *token_list,
										t_redir *cur_redir,
										t_cmd **head, t_cmd **tail)
{
	t_cmd	*cmd_data;
	size_t	arg_count;

	if (token_list->type != WORD)
		return (cleanup_cmd_list(*head));
	cmd_data = create_new_cmd_node(token_list->val, cur_redir);
	if (!cmd_data)
		return (cleanup_cmd_list(*head));
	arg_count = count_arguments(token_list->next);
	if (fill_arguments(cmd_data, token_list->next, &arg_count) < 0)
		return (cleanup_cmd_list(*head));
	add_new_cmd_to_cmd_lst(head, tail, cmd_data);
	return (NULL);
}

t_redir	*check_if_token_need_redir(t_token **token_list, t_token *cur_token, t_redir *cur_redir)
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

t_cmd	*fill_cmd_lst(t_token *token_list, t_redir *redir_list) // the one with free bug but otherwise work
{
	t_cmd	*head;
	t_cmd	*tail;
	t_token	*cur_token;
	t_redir	*cur_redir;

	if (token_list && token_list->val && is_special_command(token_list->val))
	{
		print_error_msg("parse error near \n");
		return (NULL);
	}
	head = NULL;
	tail = NULL;
	cur_redir = redir_list;
	while (token_list != NULL)
	{
		if (create_cmd_from_tokens(token_list, cur_redir, &head, &tail))
			return (NULL);
		cur_token = find_next_pipe_symbol(token_list);
		if (cur_token != NULL && cur_token->type == PIPE)
			cur_redir = check_if_token_need_redir(&token_list,
					cur_token, cur_redir);
		else
			break ;
	}
	return (head);
}

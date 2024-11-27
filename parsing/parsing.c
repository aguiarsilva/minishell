

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

static t_token	*find_next_pipe_symbol(t_token *token_list)
{
	t_token	*cur;

	cur = token_list->next;
	while (cur != NULL && cur->type != PIPE)
		cur = cur->next;
	return (cur);
}

static t_cmd	*create_cmd_from_tokens(t_token *token_list,
										t_redir *redir_list,
										t_cmd **head, t_cmd **tail)
{
	t_cmd	*cmd_data;
	size_t	arg_count;

	if (token_list->type != WORD)
	{
		// fprintf(stderr, "DEBUG: First token is not a command (WORD)\n");
		return (cleanup_cmd_list(*head));
	}
	cmd_data = create_new_cmd_node(token_list->val, redir_list);
	if (!cmd_data)
		return (cleanup_cmd_list(*head));
	arg_count = count_arguments(token_list->next);
	if (fill_arguments(cmd_data, token_list->next, &arg_count) < 0)
		return (cleanup_cmd_list(*head));
	add_new_cmd_to_cmd_lst(head, tail, cmd_data);
	return (NULL);
}

t_cmd	*fill_cmd_lst(t_token *token_list, t_redir *redir_list)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_token	*cur;

	if (token_list && token_list->val && is_special_command(token_list->val))
		return (NULL);
	head = NULL;
	tail = NULL;
	while (token_list != NULL)
	{
		if (create_cmd_from_tokens(token_list, redir_list, &head, &tail))
			return (NULL);
		cur = find_next_pipe_symbol(token_list);
		if (cur != NULL && cur->type == PIPE)
			token_list = cur->next;
		else
			break ;
	}
	return (head);
}

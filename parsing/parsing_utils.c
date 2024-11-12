

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

// Check if token should be skipped
bool	is_skippable_token(t_token *prev, t_token *cur)
{
	// No previous token, can't be a redirection file
	if (prev == NULL)
		return (false);

	// Not a redirection token
	if (prev->type != REDIR_OUT && prev->type != REDIR_IN)
		return (false);

	// Not a word token (potential filename)
	if (get_token_type(cur->val) != WORD)
		return (false);

	// If we've reached here, it's a redirection file
	return (true);
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
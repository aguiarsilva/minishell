

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
	{
		// fprintf(stderr, "DEBUGSkipping due to %s; cur val = %s\n",
		// 	prev->type == APPEND ? "APPEND" : "HEREDOC", cur->val); // Debug print
		return (true);
	}
	if (cur->eof_flag == true)
	{
		// fprintf(stderr, "DEBUG Skipping due to EOF flag; cur val = %s\n", cur->val); // Debug print
		return (true);
	}
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


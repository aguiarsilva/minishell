

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

// Check if token should be skipped
bool	is_skippable_token(t_token *prev, t_token *cur)
{
	// Check for a valid previous token; required for redirection
	if (prev == NULL)
		return (false);
	// Debugging output to track values
//	printf("prev val = %s, prev type = %d; cur val = %s, cur type = %d\n",
//		   prev->val, prev->type, cur->val, cur->type);

// Check for specific redirection types that make the token skippable
	if ((prev->type == APPEND || prev->type == HEREDOC) && cur->type == WORD)
	{
		printf("Skipping due to %s; cur val = %s\n",
			prev->type == APPEND ? "APPEND" : "HEREDOC", cur->val); // Debug print
		return (true);
	}
	// if (prev->type == REDIR_IN && cur->type == WORD)
	// {
	// 	printf("Skipping due to redir detected; cur val = %s\n", cur->val); // Debug print
	// 	return (true);
	// }
	// Check if the current token has EOF flag set
	if (cur->eof_flag == true)
	{
		printf("Skipping due to EOF flag; cur val = %s\n", cur->val); // Debug print
		return (true);
	}
	// Check if the previous token is a redirection operator
	if (prev->type != REDIR_OUT && prev->type != REDIR_IN)
		return (false);

	// Check if the current token is a word (possible filename)
	if (get_token_type(cur->val) != WORD)
		return (false);

	// All checks passed; it is a skippable redirection file token
	return (true);
}

bool	is_special_command(char *cmd)
{
	if (!cmd)
		return false;
	if (ft_strcmp(cmd, ":") == 0)  // null command
		return true;
	if (ft_strcmp(cmd, "!") == 0)  // history expansion marker
		return true;
	return false;
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

bool is_quote(char c)
{
	return (c == '\'' || c == '"');
}

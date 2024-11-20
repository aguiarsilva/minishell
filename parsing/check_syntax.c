

#include "../lib/minishell.h"

bool	is_valid_redirection_syntax(t_token *token_list)
{
	t_token	*current;
	int		consecutive_count;

	current = token_list;
	consecutive_count = 0;
	while (current)
	{
		if (current->type == REDIR_IN || current->type == REDIR_OUT
			|| current->type == APPEND || current->type == HEREDOC
			|| current->type == PIPE)
		{
			consecutive_count++;
			if (consecutive_count > 2)
				return (false);
			if (!current->next || current->next->type != WORD)
				return (false);
		}
		else
		{
			consecutive_count = 0;
		}
		current = current->next;
	}
	return (true);
}

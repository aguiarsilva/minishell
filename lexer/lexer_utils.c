#include "../lib/minishell.h"

t_type	get_token_type(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return REDIR_IN;
	else if (ft_strcmp(token, ">") == 0)
		return REDIR_OUT;
	else if (ft_strcmp(token, ">>") == 0)
		return APPEND;
	else if (ft_strcmp(token, "<<") == 0)
		return HEREDOC;
	else if (ft_strcmp(token, "|") == 0)
		return PIPE;
	else
		return WORD;  // Default type is WORD for commands/arguments
}




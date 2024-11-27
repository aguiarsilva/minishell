
#include "../lib/minishell.h"

void	handle_quote(int *in_quotes, char *quote_type, char current_char)
{
	if (*in_quotes)
	{
		*in_quotes = 0;
		*quote_type = 0;
	}
	else
	{
		*in_quotes = 1;
		*quote_type = current_char;
	}
}

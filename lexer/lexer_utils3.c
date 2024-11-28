
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

bool	analyze_buffer_for_expansion(t_parser_context *ctx)
{
	int		i;
	char	*buf;
	bool	contains_dollar_sign;
	bool	contains_quotes;

	i = 0;
	contains_dollar_sign = false;
	contains_quotes = false;
	buf = ctx->state->buffer;
	while (i < ctx->state->buf_index)
	{
		if (buf[i] == '$')
			contains_dollar_sign = true;
		if (buf[i] == '\'' || buf[i] == '"')
			contains_quotes = true;
		i++;
	}
	if (contains_dollar_sign && contains_quotes)
		return (false);
	return (true);
}
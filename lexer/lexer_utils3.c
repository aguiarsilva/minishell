/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:12:02 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/11/29 01:12:27 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	size_t		i;
	char		*buf;
	bool		contains_dollar_sign;
	int			in_quotes;
	char		quote_type;

	i = 0;
	contains_dollar_sign = false;
	in_quotes = 0;
	quote_type = 0;
	buf = ctx->state->buffer;
	while (i < ctx->state->buf_index)
	{
		if (buf[i] == '\'' || buf[i] == '"')
		{
			if (!in_quotes || quote_type == buf[i])
				handle_quote(&in_quotes, &quote_type, buf[i]);
		}
		if (i + 1 < ctx->state->buf_index && ft_isalnum(buf[i + 1]))
			contains_dollar_sign = true;
		i++;
	}
	return (contains_dollar_sign);
}

// bool	analyze_buffer_for_expansion(t_parser_context *ctx)
// {
// 	size_t		i;
// 	char	*buf;
// 	bool	contains_dollar_sign;
// 	bool	contains_quotes;
//
// 	i = 0;
// 	contains_dollar_sign = false;
// 	contains_quotes = false;
// 	buf = ctx->state->buffer;
// 	while (i < ctx->state->buf_index)
// 	{
// 		if (buf[i] == '$')
// 			contains_dollar_sign = true;
// 		if (buf[i] == '\'' || buf[i] == '"')
// 			contains_quotes = true;
// 		i++;
// 	}
// 	if (contains_dollar_sign && contains_quotes)
// 		return (false);
// 	return (true);
// }

int	is_escape_character(char c)
{
	return (c == '\\');
}

void	toggle_escape_state(int *is_escaped)
{
	*is_escaped = !(*is_escaped);
}

void	handle_quote_state(t_parser_context *ctx, char c,
		char *current_quote)
{
	if (!ctx->state->in_quotes)
	{
		ctx->state->in_quotes = 1;
		ctx->state->quote_type = c;
		ctx->state->was_quoted = 1;
		*current_quote = c;
	}
	else if (ctx->state->quote_type == c)
	{
		ctx->state->in_quotes = 0;
		ctx->state->quote_type = 0;
		*current_quote = 0;
	}
	ctx->state->buffer[ctx->state->buf_index++] = c;
}

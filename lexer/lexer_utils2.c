/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:11:22 by baguiar-          #+#    #+#             */
/*   Updated: 2024/11/25 13:11:29 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	should_process_double_char(t_char_context *char_ctx)
{
	char	current;
	char	next;

	if (char_ctx->current_index + 1 >= char_ctx->input_length)
		return (0);
	current = char_ctx->input[char_ctx->current_index];
	next = char_ctx->input[char_ctx->current_index + 1];
	if (current == '<' && next == '<')
		return ('<');
	if (current == '>' && next == '>')
		return ('>');
	return (0);
}

void	process_double_char(t_parser_context *ctx, char c, size_t *i)
{
	char	double_char[3];
	t_token	*double_token;

	double_char[0] = c;
	double_char[1] = c;
	double_char[2] = '\0';
	flush_buffer(ctx);
	double_token = make_token(double_char, get_token_type(double_char));
	add_new_token_to_lst(&ctx->tokens->head, &ctx->tokens->tail, double_token);
	(*i)++;
}

void	handle_non_quoted_special_cases(t_parser_context *ctx,
			t_char_context *char_ctx, char c)
{
	int	double_char;

	if (ft_isspace(c))
		flush_buffer(ctx);
	else if (!ctx->state->was_quoted && (c == '|'
			|| is_equals_special(c, char_ctx, ctx->state)))
		process_special_char(c, ctx);
	else
	{
		double_char = should_process_double_char(char_ctx);
		if (double_char)
			process_double_char(ctx, double_char, &char_ctx->current_index);
		else
			ctx->state->buffer[ctx->state->buf_index++] = c;
	}
}

void	handle_special_cases(t_parser_context *ctx, t_char_context *char_ctx)
{
	char	c;
	int		is_escaped_quote;

	c = char_ctx->input[char_ctx->current_index];
	is_escaped_quote = char_ctx->current_index == 0
		|| char_ctx->input[char_ctx->current_index - 1] != '\\';
	if (c == '"' && is_escaped_quote)
	{
		treat_quotes(c, ctx->state);
		return ;
	}
	if (!ctx->state->in_quotes)
	{
		handle_non_quoted_special_cases(ctx, char_ctx, c);
		return ;
	}
	ctx->state->buffer[ctx->state->buf_index++] = c;
}

void remove_quotes(char *str, int *was_quoted) {
	int i, j;
	int in_quotes = 0;
	char quote_type = 0;

	if (!str) return;
	*was_quoted = 0;  // Initialize to not quoted

	for (i = 0, j = 0; str[i] != '\0'; i++) {
		if ((str[i] == '"' || str[i] == '\'') && (!in_quotes || quote_type == str[i])) {
			*was_quoted = 1;  // Mark that this string was quoted
			if (!in_quotes) {
				in_quotes = 1;
				quote_type = str[i];
			} else {
				in_quotes = 0;
				quote_type = 0;
			}
			continue;
		}
		str[j++] = str[i];
	}
	str[j] = '\0';
}

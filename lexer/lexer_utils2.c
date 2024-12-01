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

void	handle_non_quoted_special_cases(t_parser_context *ctx, // old
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
 // void handle_non_quoted_special_cases(t_parser_context *ctx, // new
 //             t_char_context *char_ctx, char c)
 // {
 //     // If the current character is a redirection symbol (> or <)
 //     if (c == '>' || c == '<')
 //     {
 //         // First, flush any existing buffer to complete the previous token
 //         flush_buffer(ctx);
 //
 //         // Find the start of the next token (the redirection symbol)
 //         size_t start = char_ctx->current_index;
 //         size_t end = start;
 //
 //         // Find the full extent of the redirection sequence
 //         while (end < char_ctx->input_length &&
 //                (char_ctx->input[end] == '>' || char_ctx->input[end] == '<'))
 //         {
 //             end++;
 //         }
 //
 //         // Create a token for the redirection symbol(s)
 //         char redirection_str[3] = {0};
 //         strncpy(redirection_str, &char_ctx->input[start], end - start);
 //         t_token *redirection_token = make_token(redirection_str,
 //             get_token_type(redirection_str));
 //         add_new_token_to_lst(&ctx->tokens->head, &ctx->tokens->tail, redirection_token);
 //
 //         // If there's a filename or other content after the redirection symbol
 //         if (end < char_ctx->input_length && !ft_isspace(char_ctx->input[end]))
 //         {
 //             // Find the end of the next token (until next space or special char)
 //             size_t token_end = end;
 //             while (token_end < char_ctx->input_length &&
 //                    !ft_isspace(char_ctx->input[token_end]) &&
 //                    char_ctx->input[token_end] != '>' &&
 //                    char_ctx->input[token_end] != '<')
 //             {
 //                 token_end++;
 //             }
 //
 //             // Create a token for the filename/content
 //             char filename_str[256] = {0};  // Adjust size as needed
 //             strncpy(filename_str, &char_ctx->input[end], token_end - end);
 //             t_token *filename_token = make_token(filename_str,
 //                 get_token_type(filename_str));
 //             add_new_token_to_lst(&ctx->tokens->head, &ctx->tokens->tail, filename_token);
 //
 //             // Update the current index
 //             char_ctx->current_index = token_end - 1;
 //         }
 //         else
 //         {
 //             // Update the current index to the last redirection symbol
 //             char_ctx->current_index = end - 1;
 //         }
 //     }
 //     else
 //     {
 //         // Existing logic for other cases
 //         if (ft_isspace(c))
 //             flush_buffer(ctx);
 //         else if (!ctx->state->was_quoted &&
 //                  (c == '|' || is_equals_special(c, char_ctx, ctx->state)))
 //             process_special_char(c, ctx);
 //         else
 //         {
 //             int double_char = should_process_double_char(char_ctx);
 //             if (double_char)
 //                 process_double_char(ctx, double_char, &char_ctx->current_index);
 //             else
 //                 ctx->state->buffer[ctx->state->buf_index++] = c;
 //         }
 //     }
 // }




void	handle_special_cases(t_parser_context *ctx, t_char_context *char_ctx,
		int *is_escaped, char *current_quote)
{
	char	current_char;

	current_char = char_ctx->input[char_ctx->current_index];
	if (is_escape_character(current_char))
	{
		toggle_escape_state(is_escaped);
		if (*is_escaped)
			return ;
	}
	else
		*is_escaped = 0;
	if ((current_char == '"' || current_char == '\'') && !(*is_escaped))
	{
		handle_quote_state(ctx, current_char, current_quote);
		return ;
	}
	if (!ctx->state->in_quotes)
	{
		handle_non_quoted_special_cases(ctx, char_ctx, current_char);
		return ;
	}
	ctx->state->buffer[ctx->state->buf_index++] = current_char;
}

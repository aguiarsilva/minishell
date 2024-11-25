/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:12:16 by baguiar-          #+#    #+#             */
/*   Updated: 2024/11/25 13:12:25 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

t_type	get_token_type(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return (REDIR_IN);
	else if (ft_strcmp(token, ">") == 0)
		return (REDIR_OUT);
	else if (ft_strcmp(token, ">>") == 0)
		return (APPEND);
	else if (ft_strcmp(token, "<<") == 0)
		return (HEREDOC);
	else if (ft_strcmp(token, "|") == 0)
		return (PIPE);
	else
		return (WORD);
}

void	flush_buffer(t_parser_context *ctx)
{
	t_token	*new_token;

	if (ctx->state->buf_index > 0)
	{
		remove_quotes(ctx->state->buffer, &ctx->state->was_quoted);
		new_token = make_word_token(ctx->state->buffer, WORD, *ctx->env_lst);
		add_new_token_to_lst(&ctx->tokens->head, &ctx->tokens->tail, new_token);
		ft_memset(ctx->state->buffer, 0, BUFFER_SIZE);
		ctx->state->buf_index = 0;
		ctx->state->was_quoted = 0;
	}
}

void	treat_quotes(char c, t_buffer_state *state)
{
	state->in_quotes = !(state->in_quotes);
	state->buffer[state->buf_index++] = c;
}

void	process_special_char(char c, t_parser_context *ctx)
{
	int		token_type;
	t_token	*special_token;
	char	special_char[2];

	flush_buffer(ctx);
	if (c == '=')
		token_type = WORD;
	else
		token_type = get_token_type((char [2]){c, '\0'});
	special_char[0] = c;
	special_char[1] = '\0';
	special_token = make_word_token(special_char, token_type, *ctx->env_lst);
	add_new_token_to_lst(&ctx->tokens->head, &ctx->tokens->tail, special_token);
}

int	is_equals_special(char c, t_char_context *char_ctx, t_buffer_state *state)
{
	if (c != '=')
		return (0);
	return (state->buf_index == 0
		|| char_ctx->current_index == char_ctx->input_length - 1
		|| ft_isspace(char_ctx->input[char_ctx->current_index + 1]));
}

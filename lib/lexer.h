/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:16:01 by baguiar-          #+#    #+#             */
/*   Updated: 2024/11/27 15:40:35 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef struct s_cmd	t_cmd;
typedef struct s_token	t_token;
typedef struct s_redir	t_redir;
//typedef struct s_lexer	t_lexer;

//lexer.c
t_token	*make_word_token(char *wd, t_type type, t_env *env_lst);
t_token	*make_token(char *wd, t_type type);
void	assign_token_type(t_token *token_list);
t_token	*create_word_list(char *input, t_env **env_lst);
bool	check_if_token_list_right(t_token *token_lst);

//lexer_init.c
void	init_buffer_state(t_buffer_state *state);
void	init_token_list(t_token_list *list);

//lexer_utils.c
t_type	get_token_type(char *token);
void	flush_buffer(t_parser_context *ctx);
void	treat_quotes(char c, t_buffer_state *state);
void	process_special_char(char c, t_parser_context *ctx);
int		is_equals_special(char c, t_char_context *char_ctx,
			t_buffer_state *state);

//lexer_utils2.c
int		should_process_double_char(t_char_context *char_ctx);
void	process_double_char(t_parser_context *ctx, char c, size_t *i);
void	handle_non_quoted_special_cases(t_parser_context *ctx,
			t_char_context *char_ctx, char c);
//void	handle_special_cases(t_parser_context *ctx, t_char_context *char_ctx); // old version
void	handle_special_cases(t_parser_context *ctx, t_char_context *char_ctx, int *is_escaped, char *current_quote);
void	remove_quotes(char *str, int *was_quoted);

//lexer_utils3.c
void	handle_quote(int *in_quotes, char *quote_type, char current_char);

#endif //LEXER_H
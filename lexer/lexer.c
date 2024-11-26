/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:16:01 by baguiar-          #+#    #+#             */
/*   Updated: 2024/11/26 10:16:01 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

t_token	*make_word_token(char *wd, t_type type, t_env *env_lst)
{
	t_token	*new_tk;
	int		len;
	char	*checked_word;

	checked_word = expand_word(wd, -1, env_lst);
	len = ft_strlen(checked_word);
	new_tk = malloc(sizeof(t_token));
	if (new_tk == NULL)
		return (NULL);
	new_tk->val = (char *)malloc(sizeof(char) * (len + 1));
	if (new_tk->val == NULL)
	{
		free(new_tk);
		return (NULL);
	}
	ft_strcpy(new_tk->val, checked_word);
	new_tk->eof_flag = false;
	new_tk->next = NULL;
	new_tk->type = type;
	free(checked_word);
	return (new_tk);
}

t_token	*make_token(char *wd, t_type type)
{
	t_token	*new_tk;
	int		len;

	len = ft_strlen(wd);
	new_tk = malloc(sizeof(t_token));
	if (new_tk == NULL)
		return (NULL);
	new_tk->val = (char *)malloc(sizeof(char) * (len + 1));
	if (new_tk->val == NULL)
	{
		free(new_tk);
		return (NULL);
	}
	ft_strcpy(new_tk->val, wd);
	new_tk->eof_flag = false;
	new_tk->next = NULL;
	new_tk->type = type;
	return (new_tk);
}

void	assign_token_type(t_token *token_list)
{
	t_token	*current;
	t_token	*previous;

	current = token_list;
	previous = NULL;
	while (current != NULL)
	{
		current->type = get_token_type(current->val);
		if (previous != NULL && get_token_type(previous->val) == HEREDOC)
			current->eof_flag = true;
		previous = current;
		current = current->next;
	}
}

t_token	*create_word_list(char *input, t_env **env_lst)
{
	t_buffer_state		state;
	t_token_list		tokens;
	t_parser_context	ctx;
	t_char_context		char_ctx;

	init_buffer_state(&state);
	init_token_list(&tokens);
	ctx.state = &state;
	ctx.tokens = &tokens;
	ctx.env_lst = env_lst;
	char_ctx.input = input;
	char_ctx.input_length = ft_strlen(input);
	char_ctx.current_index = 0;
	while (char_ctx.current_index < char_ctx.input_length)
	{
		handle_special_cases(&ctx, &char_ctx);
		char_ctx.current_index++;
	}
	flush_buffer(&ctx);
	return (tokens.head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:10:07 by baguiar-          #+#    #+#             */
/*   Updated: 2024/11/25 13:10:23 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	init_buffer_state(t_buffer_state *state)
{
	ft_memset(state->buffer, 0, BUFFER_SIZE);
	state->buf_index = 0;
	state->was_quoted = 0;
	state->in_quotes = 0;
}

void	init_token_list(t_token_list *list)
{
	list->head = NULL;
	list->tail = NULL;
}

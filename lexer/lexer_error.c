/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 00:37:56 by baguiar-          #+#    #+#             */
/*   Updated: 2024/11/30 00:37:56 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

t_token	*check_for_unmatched_quotes_and_handle_error(char *input)
{
	int	quote_check_result;

	quote_check_result = check_for_unmatched_quotes(input, ft_strlen(input));
	if (quote_check_result != 0)
	{
		print_error_msg(ERR_UNEVENQUOTES);
		return (NULL);
	}
	return ((t_token *)1);
}

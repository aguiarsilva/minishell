/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_free2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:02:34 by baguiar-          #+#    #+#             */
/*   Updated: 2024/11/29 01:02:38 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	free_tk(t_token *tk_list)
{
	t_token	*tk_list_placeholder;

	if (!tk_list)
		return ;
	while (tk_list)
	{
		free(tk_list->val);
		tk_list_placeholder = tk_list;
		tk_list = tk_list->next;
		free(tk_list_placeholder);
	}
}

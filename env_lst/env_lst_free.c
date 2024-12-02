/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:16:57 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/11/29 01:07:06 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	free_env_node(t_env *node)
{
	if (node == NULL)
		return ;
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

void	free_env_lst(t_env **head)
{
	t_env	*tmp;

	if (head == NULL || *head == NULL)
		return ;
	while (*head != NULL)
	{
		tmp = (*head)->next;
		free_env_node(*head);
		*head = tmp;
	}
	*head = NULL;
}

void	free_all(t_cmd *cmd_head, t_env **env_head)
{
	free_cmd_list(cmd_head);
	free_env_lst(env_head);
}

t_cmd	*cleanup_cmd_list(t_cmd *head)
{
	free_cmd_list(head);
	return (NULL);
}

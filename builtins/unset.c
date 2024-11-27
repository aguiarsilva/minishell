/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:26:20 by baguiar-          #+#    #+#             */
/*   Updated: 2024/11/26 11:26:20 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static void	remove_env_var(t_env **env_lst, char *key)
{
	t_env	*current;
	t_env	*prev;

	prev = NULL;
	current = *env_lst;
	while (current)
	{
		if (current->key && ft_strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
				*env_lst = current->next;
			else
				prev->next = current->next;
			free_env_node(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

static bool	is_valid_env_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (false);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (false);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

int	unset_builtin(char **args, t_env **env_lst)
{
	int	i;
	int	exit_status;

	exit_status = 0;
	if (!args || !args[0])
		return (0);
	i = 0;
	while (args[i])
	{
		if (is_valid_env_identifier(args[i]) == false)
		{
			ft_putstr_fd("unset: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			exit_status = 1;
		}
		else
			remove_env_var(env_lst, args[i]);
		i++;
	}
	return (exit_status);
}

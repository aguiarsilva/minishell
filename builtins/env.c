/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:12:09 by baguiar-          #+#    #+#             */
/*   Updated: 2024/11/25 11:14:55 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static void	print_env_var(t_env *env, bool export)
{
	if (env->value)
	{
		if (export)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(env->key, 1);
			ft_putchar_fd('=', 1);
			ft_putchar_fd('\"', 1);
			ft_putstr_fd(env->value, 1);
			ft_putchar_fd('\"', 1);
			ft_putchar_fd('\n', 1);
		}
		else
		{
			ft_putstr_fd(env->key, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(env->value, 1);
			ft_putchar_fd('\n', 1);
		}
	}
}

void	print_env_list(t_env *env_lst, bool export)
{
	while (env_lst)
	{
		print_env_var(env_lst, export);
		env_lst = env_lst->next;
	}
}

int	env_builtin(t_cmd *cmd_data, t_env *env_lst)
{
	if (cmd_data->args && cmd_data->args[0])
	{
		if (cmd_data->args[0][0] == '-')
		{
			ft_putstr_fd("env: illegal option -- ", 2);
			ft_putchar_fd(cmd_data->args[0][1], 2);
			ft_putstr_fd("\nusage: env\n", 2);
			return (1);
		}
		else
		{
			ft_putstr_fd("env: '", 2);
			ft_putstr_fd(cmd_data->args[0], 2);
			ft_putstr_fd("': No such file or directory\n", 2);
			return (127);
		}
	}
	print_env_list(env_lst, NO_EXPORT);
	return (0);
}

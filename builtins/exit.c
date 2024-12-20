/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:16:01 by baguiar-          #+#    #+#             */
/*   Updated: 2024/11/26 10:54:11 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	is_valid_number(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static void	cleanup_and_exit(t_cmd *cmd, t_env **env_lst, int exit_code)
{
	free_all(cmd, env_lst);
	exit(exit_code);
}

int	builtin_exit(t_cmd *cmd, t_env **env_lst)
{
	char	*exitcode_str;
	int		exit_code;

	if (cmd == NULL)
	{
		free_env_lst(env_lst);
		exit(0);
	}
	if (!cmd->args[0])
	{
		exitcode_str = get_key_in_env_lst(*env_lst, "EC");
		exit_code = ft_atoi(exitcode_str);
		free(exitcode_str);
		cleanup_and_exit(cmd, env_lst, exit_code);
	}
	if (!is_valid_number(cmd->args[0]))
		print_custom_msg_and_exit(EXIT_NUMERIC_ARG_REQ, 2);
	if (cmd->args[1])
		return (print_error_msg(EXIT_TOO_MANY_ARGS));
	exit_code = (unsigned char)ft_atoll(cmd->args[0]);
	cleanup_and_exit(cmd, env_lst, exit_code);
	return (0);
}

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

int	builtin_exit(t_cmd *cmd, t_env *env) // maybe limit exit code between 0 255 use modulo i guess
{
	char	*exitcode_str;
	int		exit_code;

	if (!cmd->args[0])
	{
		exitcode_str = get_key_in_env_lst(env, "EC");
		exit_code = ft_atoi(exitcode_str);
		// printf("DEBUG: exitcode with no arguments = %d\n", exit_code);
		free(exitcode_str);
		exit(exit_code);
	}
	if (!is_valid_number(cmd->args[0]))
	{
		// fprintf(stderr, EXIT_NUMERIC_ARG_REQ);
		exit(2);
	}
	if (cmd->args[1])
	{
		// fprintf(stderr, EXIT_TOO_MANY_ARGS);
		return (1);
	}
	exit_code = (unsigned char)ft_atoll(cmd->args[0]);
	fprintf(stderr, "exit_code: %d when using builtin exit \n", exit_code);
	exit(exit_code);
}

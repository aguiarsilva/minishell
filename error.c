/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 23:56:13 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/12/01 23:56:13 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/minishell.h"

int	print_error_msg(char *error)
{
	write(STDERR_FILENO, error, ft_strlen(error));
	return (1);
}

void	print_cmd_not_found_and_exit(char *cmd, char *exec_path, char **env)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found: \n", STDERR_FILENO);
	free(exec_path);
	ft_free_array(env);
	exit(127);
}

void	print_custom_msg_and_exit(char *error, int exit_code)
{
	ft_putstr_fd(error, STDOUT_FILENO);
	exit (exit_code);
}

void	print_error_msg_and_exit(char *error)
{
	perror(error);
	exit (EXIT_FAILURE);
}

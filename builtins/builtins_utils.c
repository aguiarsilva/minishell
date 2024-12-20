/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:27:25 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/11/26 11:33:29 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	check_for_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0
		&& ft_strlen(cmd) == 4)
		return (1);
	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0
		&& ft_strlen(cmd) == 2)
		return (1);
	else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0
		&& ft_strlen(cmd) == 3)
		return (1);
	else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0
		&& ft_strlen(cmd) == 6)
		return (1);
	else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0
		&& ft_strlen(cmd) == 5)
		return (1);
	else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0
		&& ft_strlen(cmd) == 3)
		return (1);
	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0
		&& ft_strlen(cmd) == 4)
		return (1);
	else
		return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exebuiltins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 00:08:07 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/12/02 00:08:07 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	run_builtin(t_cmd *cmd_data, t_env **env_lst)
{
	int	exit_code;

	exit_code = 0;
	if (ft_strncmp(cmd_data->cmd, "echo", ft_strlen(cmd_data->cmd)) == 0 && \
			ft_strlen(cmd_data->cmd) == 4)
		exit_code = echo(cmd_data);
	else if (!ft_strncmp(cmd_data->cmd, "export", ft_strlen(cmd_data->cmd)) && \
			ft_strlen(cmd_data->cmd) == 6)
		exit_code = export_builtin(cmd_data->args, env_lst);
	else if (!ft_strncmp(cmd_data->cmd, "pwd", ft_strlen(cmd_data->cmd)) && \
			ft_strlen(cmd_data->cmd) == 3)
		exit_code = pwd();
	else if (!ft_strncmp(cmd_data->cmd, "cd", ft_strlen(cmd_data->cmd)) && \
			ft_strlen(cmd_data->cmd) == 2)
		exit_code = cd_dir(cmd_data, *env_lst);
	else if (!ft_strncmp(cmd_data->cmd, "env", ft_strlen(cmd_data->cmd)) && \
			ft_strlen(cmd_data->cmd) == 3)
		exit_code = env_builtin(cmd_data, *env_lst);
	else if (!ft_strncmp(cmd_data->cmd, "unset", ft_strlen(cmd_data->cmd)) && \
			ft_strlen(cmd_data->cmd) == 5)
		exit_code = unset_builtin(cmd_data->args, env_lst);
	else if (!ft_strncmp(cmd_data->cmd, "exit", ft_strlen(cmd_data->cmd)) && \
			ft_strlen(cmd_data->cmd) == 4)
		exit_code = builtin_exit(cmd_data, env_lst);
	return (exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:16:28 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/11/26 12:02:29 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static char	*combine_command_and_args(char *cmd, char **args)
{
	size_t	cmd_length;
	size_t	args_length;
	int		i;
	char	*full_cmd;

	cmd_length = strlen(cmd);
	args_length = 0;
	i = 0;
	while (args && args[i])
	{
		args_length += strlen(args[i]) + 1;
		i++;
	}
	full_cmd = safe_malloc(cmd_length + args_length + 1);
	if (!full_cmd)
		exit(EXIT_FAILURE);
	ft_strcpy(full_cmd, cmd);
	i = 0;
	while (args && args[i])
	{
		ft_strcat(full_cmd, " ");
		ft_strcat(full_cmd, args[i]);
		i++;
	}
	return (full_cmd);
}

void	run_cmd(t_cmd *cmd_data, t_env **env_lst)
{
	char	*full_cmd;
	char	**split_cmd;
	char	*exec_path;
	char	**env;

	full_cmd = combine_command_and_args(cmd_data->cmd, cmd_data->args);
	env = env_list_to_array(*env_lst);
	exec_path = get_exec_path(cmd_data->cmd, env);
	if (exec_path == NULL)
		print_cmd_not_found_and_exit(cmd_data->cmd, exec_path, env);
	split_cmd = parse_command_with_quotes(full_cmd);
	if (execve(exec_path, split_cmd, env) == -1)
	{
		free(exec_path);
		ft_free_array(split_cmd);
		exit(EXIT_FAILURE);
	}
	free(exec_path);
	ft_free_array(split_cmd);
}

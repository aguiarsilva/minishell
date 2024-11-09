/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:16:28 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/10/20 16:16:28 by tbui-quo         ###   ########.fr       */
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
//	fprintf(stderr, "cmd_data->cmd: %s\n", cmd_data->cmd);
	full_cmd = combine_command_and_args(cmd_data->cmd, cmd_data->args); // temporary
	// fprintf(stderr, "full_cmd after combine call: %s\n", full_cmd);
	env = env_list_to_array(*env_lst);
	exec_path = get_exec_path(cmd_data->cmd, env);
	split_cmd = parse_command_with_quotes(full_cmd);
//	 fprintf(stderr, "Executable Path: %s\n", exec_path);

	// fprintf(stderr, "Command arguments:\n");
	// for (int i = 0; split_cmd[i]; i++)
	// {
	// 	fprintf(stderr, "split_cmd[%d]: %s\n", i, split_cmd[i]);
	// }
	// free(cmd);
	if (execve(exec_path, split_cmd, env) == -1)
	{
		fprintf(stderr, "Error executing %s: %s\n", exec_path, strerror(errno)); // maybe its possible to return with my error function
		free(exec_path);
		ft_free_array(split_cmd);
		exit(EXIT_FAILURE);
	}
	free(exec_path);
	ft_free_array(split_cmd);
	print_error_msg_and_exit(ERR_UNKNOWN);
}

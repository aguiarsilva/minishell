/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:51:13 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/11/20 12:51:14 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	set_pwd_env(t_env *env_lst, char *target_dir)
{
	char	*pwd;

	pwd = get_key_in_env_lst(env_lst, "PWD");
	if (set_value_in_env_lst(env_lst, "PWD", target_dir))
		return (1);
	if (pwd)
		free(pwd);
	return (0);
}

static int	cd_home(t_cmd *cmd, t_env *env_lst)
{
	char	*home_path;

	if (cmd->args[0] != NULL)
		return (1);
	if (cmd->args[0] == NULL)
	{
		home_path = getenv("HOME");
		if (home_path)
		{
			set_pwd_env(env_lst, home_path);
			chdir(home_path);
		}
	}
	return (0);
}

int	change_directory(t_cmd *cmd_lst, t_env *env_lst)
{
	char	*current_work_directory;

	if (chdir(cmd_lst->args[0]) == PATH_VALID)
	{
		current_work_directory = getcwd(NULL, 0);
		if (current_work_directory == NULL)
		{
			ft_putstr_fd(ERR_NO_CUR_DIR, STDERR_FILENO);
			ft_putstr_fd(ERR_PARENT_DIR_ACCESS, STDERR_FILENO);
			current_work_directory = ft_strdup(getenv("HOME"));
			if (current_work_directory[0] == '\0')
				return (1);
		}
		set_pwd_env(env_lst, current_work_directory);
		free(current_work_directory);
	}
	else
		return (ft_putstr_fd(ERR_NO_SUCH_DIR, STDERR_FILENO), 1);
	return (0);
}

int	cd_dir(t_cmd *cmd_lst, t_env *env_lst)
{
	if (cd_home(cmd_lst, env_lst) == CMD_NO_ARGUMENTS)
		return (1);
	return (change_directory(cmd_lst, env_lst));
}

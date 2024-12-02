/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 22:29:15 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/12/01 22:29:15 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static void	handle_builtin_command(t_cmd *cmd, t_env **env_lst)
{
	int	builtin_result;

	builtin_result = run_builtin(cmd, env_lst);
	cmd->exit_code = builtin_result;
	update_exit_code(*env_lst, builtin_result);
}

void	run_builtin_or_execute(t_cmd *cmd_lst, t_env **env_lst)
{
	if (cmd_lst->builtin)
		handle_builtin_command(cmd_lst, env_lst);
	else
	{
		run_cmd(cmd_lst, env_lst);
		print_error_msg_and_exit(ERR_UNKNOWN);
	}
}

void	run_process(t_cmd *cmd_lst, t_env **env_lst)
{
	size_t	cmd_count;

	if (cmd_lst == NULL)
		return ;
	if (cmd_lst->cmd && cmd_lst->cmd[0] && is_special_command(&cmd_lst->cmd[0]))
		return ;
	cmd_count = get_cmd_lst_size(cmd_lst);
	if (cmd_count == 1 && cmd_lst->builtin && cmd_lst->redir == NULL)
		handle_builtin_command(cmd_lst, env_lst);
	else
		run_pipeline(cmd_lst, env_lst);
}

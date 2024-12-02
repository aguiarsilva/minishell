/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:46:07 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/11/28 15:46:07 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	check_child_status(pid_t child_pid, t_cmd *cmd_lst)
{
	int	status;
	int	exit_code;

	if (waitpid(child_pid, &status, 0) == -1)
		return ;
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		cmd_lst->exit_code = exit_code;
	}
	else
		cmd_lst->exit_code = -1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 00:58:44 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/11/28 00:58:44 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	handle_parent_pipes_and_process(pid_t process_id, t_cmd *cmd,
										t_pipes *pipes)
{
	close_pipe_fds(pipes->prev_pipe_fd);
	update_prev_pipe_fds(pipes);
	check_child_status(process_id, cmd);
}

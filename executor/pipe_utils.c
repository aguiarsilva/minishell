/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:15:20 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/11/28 15:15:20 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	init_pipe_fds(t_pipes *pipes)
{
	pipes->pipe_fd[0] = -1;
	pipes->pipe_fd[1] = -1;
	pipes->prev_pipe_fd[0] = -1;
	pipes->prev_pipe_fd[1] = -1;
}

void	close_pipe_fds(int pipe_fd[2])
{
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
}

void	update_prev_pipe_fds(t_pipes *pipes)
{
	pipes->prev_pipe_fd[0] = pipes->pipe_fd[0];
	pipes->prev_pipe_fd[1] = pipes->pipe_fd[1];
}

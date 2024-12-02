/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 00:13:35 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/12/02 00:13:35 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static void	handle_first_command(t_cmd *cmd, int pipe_fd[2])
{
	handle_file_redirections(cmd);
	if (cmd->next && pipe_fd[1] != -1
		&& (!cmd->redir
			|| (cmd->redir->type != REDIR_OUT
				&& cmd->redir->type != APPEND)))
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
}

static void	handle_middle_command(t_cmd *cmd, int prev_pipe_fd[2],
									int pipe_fd[2], size_t cmd_count)
{
	handle_pipe_redirections(cmd, prev_pipe_fd, pipe_fd, cmd_count);
}

static void	handle_last_command(t_cmd *cmd, int prev_pipe_fd[2])
{
	if (prev_pipe_fd[0] != -1)
	{
		dup2(prev_pipe_fd[0], STDIN_FILENO);
		close(prev_pipe_fd[0]);
	}
	if (prev_pipe_fd[1] != -1)
		close(prev_pipe_fd[1]);
	handle_file_redirections(cmd);
}

void	handle_child_process(t_cmd *cmd, t_env **env_lst,
			t_pipes *pipes, size_t cmd_position)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (cmd_position == 0)
		handle_first_command(cmd, pipes->pipe_fd);
	else if (!cmd->next)
		handle_last_command(cmd, pipes->prev_pipe_fd);
	else
		handle_middle_command(cmd, pipes->prev_pipe_fd, pipes->pipe_fd,
			cmd_position);
	run_builtin_or_execute(cmd, env_lst);
}

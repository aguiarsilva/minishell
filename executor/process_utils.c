/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:38:03 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/12/02 14:38:03 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static pid_t	create_process(void)
{
	pid_t	process_id;

	process_id = fork();
	if (process_id == -1)
		print_error_msg_and_exit(ERR_FORK);
	return (process_id);
}

static void	create_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
		print_error_msg_and_exit(ERR_PIPE);
}

static void	execute_command(t_cmd *current, t_env **env_lst,
							t_pipes *pipes,
							size_t cmd_position)
{
	pid_t	process_id;

	if (current->next != NULL)
		create_pipe(pipes->pipe_fd);
	process_id = create_process();
	if (process_id == 0)
	{
		signal(SIGQUIT, sig_quit);
		signal(SIGINT, SIG_DFL);
		handle_child_process(current, env_lst, pipes, cmd_position);
		exit(EXIT_FAILURE);
	}
	handle_parent_pipes_and_process(process_id, current, pipes);
	if (!current->next && cmd_position == 0)
		update_exit_code(*env_lst, current->exit_code);
}

void	run_pipeline(t_cmd *cmd_list, t_env **env_lst)
{
	size_t	cmd_position;
	t_pipes	pipes;
	t_cmd	*current;
	int		last_exit_code;

	cmd_position = 0;
	init_pipe_fds(&pipes);
	current = cmd_list;
	while (current != NULL)
	{
		execute_command(current, env_lst, &pipes, cmd_position);
		if (current->next == NULL)
			last_exit_code = current->exit_code;
		current = current->next;
		cmd_position++;
	}
	update_exit_code(*env_lst, last_exit_code);
}

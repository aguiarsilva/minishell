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
							int prev_pipe_fd[2], int pipe_fd[2],
							size_t cmd_position)
{
	pid_t	process_id;

	if (current->next != NULL)
		create_pipe(pipe_fd);
	process_id = create_process();

	if (process_id == 0)
	{
		signal(SIGQUIT, sig_quit);
		signal(SIGINT, SIG_DFL);
		handle_child_process(current, env_lst, prev_pipe_fd,
			pipe_fd, cmd_position);
		exit(EXIT_FAILURE);
	}
	handle_parent_pipes_and_process(process_id, current, prev_pipe_fd, pipe_fd);

	if (!current->next && cmd_position == 0)
		update_exit_code(*env_lst, current->exit_code);
}

static void	run_pipeline(t_cmd *cmd_list, t_env **env_lst)
{
	int		pipe_fd[2];
	int		prev_pipe_fd[2]; // maybe combine this into a struct
	size_t	cmd_position;
	t_cmd	*current;
	int		last_exit_code;

	cmd_position = 0;
	init_pipe_fds(pipe_fd, prev_pipe_fd);
	current = cmd_list;
	while (current != NULL)
	{
		execute_command(current, env_lst, prev_pipe_fd, pipe_fd, cmd_position);
		if (current->next == NULL)
			last_exit_code = current->exit_code;
		current = current->next;
		cmd_position++;
	}
	update_exit_code(*env_lst, last_exit_code);
}

void	handle_builtin_command(t_cmd *cmd, t_env **env_lst)
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
	{
		free_cmd_list(cmd_lst);
		return ;
	}
	if (cmd_lst->cmd && cmd_lst->cmd[0] && is_special_command(&cmd_lst->cmd[0]))
		return ;
	cmd_count = get_cmd_lst_size(cmd_lst);
	if (cmd_count == 1 && cmd_lst->builtin && cmd_lst->redir == NULL)
		handle_builtin_command(cmd_lst, env_lst);
	else
		run_pipeline(cmd_lst, env_lst);
}

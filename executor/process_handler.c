
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
	fprintf(stderr, "DEBUG: Created new pipe: [%d, %d]\n", pipe_fd[0], pipe_fd[1]);
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
		handle_child_process(current, env_lst, prev_pipe_fd, pipe_fd, cmd_position);
		exit(EXIT_FAILURE); // Should not reach here
	}

	// Parent process handling
	handle_parent_pipes_and_process(process_id, current, prev_pipe_fd, pipe_fd);
//	printf("DEBUG after handled parent exit check exitcode of cmd %s, %d\n", current->cmd, current->exit_code);
	update_env_exit_code(*env_lst, "EC", current);
//	print_env_list(*env_lst);
}

static void	run_pipeline(t_cmd *cmd_list, t_env **env_lst)
{
	int		pipe_fd[2];
	int		prev_pipe_fd[2]; // maybe combine this into a struct
	size_t	cmd_position;
	t_cmd	*current;

	cmd_position = 0;
	init_pipe_fds(pipe_fd, prev_pipe_fd);
	current = cmd_list;

	while (current != NULL)
	{
		fprintf(stderr, "DEBUG: Processing command: %s at position %zu\n",
			current->cmd, cmd_position);
		execute_command(current, env_lst, prev_pipe_fd, pipe_fd, cmd_position);
		current = current->next;
		cmd_position++;
	}
}

void handle_builtin_command(t_cmd *cmd_lst, t_env **env_lst)
{
	int	ec_for_builtin;

	if (cmd_lst->builtin)
	{
		ec_for_builtin = run_builtin(cmd_lst, env_lst);
		update_env_exit_code_for_builtins(*env_lst, ec_for_builtin);
	}
}

void	run_builtin_or_execute(t_cmd *cmd_lst, t_env **env_lst)
{
	if (cmd_lst->builtin)
		handle_builtin_command(cmd_lst, env_lst);
		// exit(run_builtin(cmd_lst, env_lst)); // should probably not exit here and just update the ec
	else
	{
		run_cmd(cmd_lst, env_lst);
		print_error_msg_and_exit(ERR_UNKNOWN);
	}
}

void	run_process(t_cmd *cmd_lst, t_env **env_lst)
{
	size_t	cmd_count;

	cmd_count = 0;
//	printf("DEBUG: run_process called for command: %s\n", cmd_lst->cmd);
	if (cmd_lst == NULL)
	{
		printf("No commands to execute\n"); //debug print
		return ;
	}
	if (cmd_lst->cmd && cmd_lst->cmd[0] && is_special_command(&cmd_lst->cmd[0]))
		return ;
	cmd_count = get_cmd_lst_size(cmd_lst);
	if (cmd_count == 1 && cmd_lst->builtin)
	{
		printf("run builtin without pipeline\n");
//		fprintf(stderr, "exit_code: %d before running straight builtin \n", (*env_lst)->exit_code);
		handle_builtin_command(cmd_lst, env_lst);
		// run_builtin(cmd_lst, env_lst);
	}
	else
	{
		printf("DEBUG: env exit_code before: %d\n", (*env_lst)->exit_code);
		printf("DEBUG: run %ld cmds\n", cmd_count); //debug print
		run_pipeline(cmd_lst, env_lst);
		printf("DEBUG: env exit_code after: %d\n", (*env_lst)->exit_code);
	}
}

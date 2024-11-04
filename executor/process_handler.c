
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

static void	execute_command(t_cmd *current, char *env[],
							int prev_pipe_fd[2], int pipe_fd[2],
							size_t cmd_position)
{
	pid_t	process_id;

	if (current->next != NULL)
		create_pipe(pipe_fd);

	process_id = create_process();

	if (process_id == 0)
	{
		handle_child_process(current, env, prev_pipe_fd, pipe_fd, cmd_position);
		exit(EXIT_FAILURE); // Should not reach here
	}

	// Parent process handling
	handle_parent_pipes_and_process(process_id, current, prev_pipe_fd, pipe_fd);
}

static void	run_pipeline(t_cmd *cmd_list, char *env[])
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

		execute_command(current, env, prev_pipe_fd, pipe_fd, cmd_position);

		current = current->next;
		cmd_position++;
	}

}

void	run_builtin_or_execute(t_cmd *cmd_data, char *env[])
{
	if (cmd_data->builtin)
		exit(run_builtin(cmd_data, env));
	else
	{
		run_cmd(cmd_data, env);
		print_error_msg_and_exit(ERR_UNKNOWN);
	}
}

void	run_process(t_cmd *cmd_list, char *env[])
{
	size_t	cmd_count;

	cmd_count = 0;
	if (cmd_list == NULL)
	{
		printf("No commands to execute\n"); //debug print
		return ;
	}
	cmd_count = get_cmd_data_list_size(cmd_list);
	if (cmd_count == 1)
		run_builtin_or_execute(cmd_list, env); //
	else if (cmd_count >= 2)
	{
		printf("run %ld cmds\n", cmd_count); //debug print
		run_pipeline(cmd_list, env);
	}
}

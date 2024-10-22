
#include "../lib/minishell.h"

// Main pipeline function
static void	run_pipeline(t_cmd *cmd_list, char *env[])
{
	int		pipe_fd[2];
	int		prev_pipe_fd[2];
	size_t	cmd_count;
	int		original_stdout;
	pid_t	process_id;

	cmd_count = 0;
	init_pipe_fds(pipe_fd, prev_pipe_fd);
	original_stdout = dup(STDOUT_FILENO);
	fprintf(stderr, "DEBUG: Original stdout: %d\n", original_stdout);
	while (cmd_list != NULL)
	{
		fprintf(stderr, "DEBUG: Processing command: %s\n", cmd_list->cmd);

		create_pipe_if_needed(cmd_list, pipe_fd);

		process_id = create_child_process(cmd_list, env, prev_pipe_fd,
										  pipe_fd, original_stdout);

		if (process_id > 0) // Parent process
			handle_parent_pipes_and_process(process_id, cmd_list,
				prev_pipe_fd, pipe_fd);

		cmd_list = cmd_list->next;
		cmd_count++;
	}

	// Cleanup // seems to do nothing
//	close_pipe_fds(prev_pipe_fd);
//	if (original_stdout != -1)
//		close(original_stdout);
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
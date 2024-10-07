
#include "../lib/minishell.h"

void run_process(t_cmd *cmd_data, char *env[])
{
	int		in_and_out_file;
	int		pipe_fd[2]; // change to count of all cmds instead of 2
	pid_t	process_id;

	// in_and_out_file = INPUT; // only for debug purposes
	// in_and_out_file = NOFILE; // only for debug purposes
	if (cmd_data->redir != NULL)
	{
		fprintf(stderr, "should be input or output file\n");
		if (cmd_data->redir->type == REDIR_IN)
			in_and_out_file = INPUT;
		else if (cmd_data->redir->type == REDIR_OUT) // maybe combine my input and output ints with t_type
			in_and_out_file = OUTPUT;
	}
	else
	{
		fprintf(stderr, "should be no file\n");
		in_and_out_file = NOFILE;
	}
	// in_and_out_file = cmd_data->redir->type; // currenty this would be 87 everytime
	// fprintf(stderr, "in_and_out_file %d\n", in_and_out_file);
	if (pipe(pipe_fd) == -1)
		print_error_msg_and_exit(ERR_PIPE);
	process_id = fork();
	if (process_id < 0)
	{
		free_cmd_data(cmd_data);
		print_error_msg_and_exit(ERR_FORK);
	}

	// In the child process
	if (process_id == 0)
	{
		run_builtin_or_execute(cmd_data, env, pipe_fd, in_and_out_file);
	}
	else
	{
		// In the parent process
		handle_parent_process(process_id, cmd_data);
	}
}

void run_cmd(t_cmd *cmd_data, char *env[])
{
	char	*full_cmd;
	char	**split_cmd;
	char	*exec_path;
//	fprintf(stderr, "cmd_data->cmd: %s\n", cmd_data->cmd);
	full_cmd = combine_command_and_args(cmd_data->cmd, cmd_data->args); // temporary
	// fprintf(stderr, "full_cmd after combine call: %s\n", full_cmd);
	exec_path = get_exec_path(cmd_data->cmd, env);
	split_cmd = parse_command_with_quotes(full_cmd);
//	 fprintf(stderr, "Executable Path: %s\n", exec_path);

	// fprintf(stderr, "Command arguments:\n");
	// for (int i = 0; split_cmd[i]; i++)
	// {
	// 	fprintf(stderr, "split_cmd[%d]: %s\n", i, split_cmd[i]);
	// }
	// free(cmd);
	if (execve(exec_path, split_cmd, env) == -1)
	{
		fprintf(stderr, "Error executing %s: %s\n", exec_path, strerror(errno)); // maybe its possible to return with my error function
		free(exec_path);
		ft_free_array(split_cmd);
		exit(EXIT_FAILURE);
	}
	free(exec_path);
	ft_free_array(split_cmd);
	print_error_msg_and_exit(ERR_UNKNOWN);
}
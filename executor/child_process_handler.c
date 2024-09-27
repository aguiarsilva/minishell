
#include "../lib/minishell.h"

// builtins needs to be able to pipe as well, currently only cmd work with pipes
void	run_builtin_or_execute(t_cmd *cmd_data, char *env[], int *pipe_fd, int in_or_out) // in_or_out will be handled by token
{
	int	input_fd;
	int	output_fd;
	char *testinputfilename = "input.txt";
	char *testoutputfilename = "output.txt";

	if (cmd_data->builtin)
		run_builtin(cmd_data, env);
	else
	{
		if (in_or_out == INPUT)
		{
			fprintf(stderr, "execute with input file\n");
			close(pipe_fd[0]);
			input_fd = open_input_or_output_file(testinputfilename, INPUT);
			dup2(input_fd, STDIN_FILENO);
			dup2(pipe_fd[1], STDOUT_FILENO); // prevents fprintf to stdout
			close(pipe_fd[1]);
			run_cmd(cmd_data, env);
			print_error_msg_and_exit(ERR_UNKNOWN);
		}
		else if (in_or_out == OUTPUT)
		{
			close(pipe_fd[1]);
			output_fd = open_input_or_output_file(testoutputfilename, OUTPUT);
			dup2(output_fd, STDOUT_FILENO);
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
			run_cmd(cmd_data, env);
			print_error_msg_and_exit(ERR_UNKNOWN);
		}
		else if (in_or_out == NOFILE)
		{
			run_cmd(cmd_data, env);
			print_error_msg_and_exit(ERR_UNKNOWN);
		}
	}
}

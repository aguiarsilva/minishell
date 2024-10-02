
#include "../lib/minishell.h"

// builtins needs to be able to pipe as well, currently only cmd work with pipes
void	run_builtin_or_execute(t_cmd *cmd_data, char *env[], int *pipe_fd, int in_or_out) // in_or_out will be handled by token
{
	int		input_fd;
	int		output_fd;
	char	*testinputfilename;
	char	*testoutputfilename;
	// testinputfilename = "input.txt";
	// testoutputfilename = "output.txt";
	fprintf(stderr, "run_builtin_or_execute \n");
	if (cmd_data == NULL) // just for debug
	{
		fprintf(stderr, "cmd_data is NULL\n");
		return; // Early exit or handle error
	}
	if (cmd_data->redir == NULL) //just for debug
	{
		fprintf(stderr, "cmd_data->redir is NULL\n");
		return; // Early exit or handle error
	}
//	testinputfilename = cmd_data->redir->file_name;
//	fprintf(stderr, "testinputfilename: %s\n", testinputfilename);
	testoutputfilename = cmd_data->redir->file_name;
		fprintf(stderr, "testoutputfilename: %s\n", testoutputfilename);
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
			// dup2(pipe_fd[1], STDOUT_FILENO); // prevents fprintf to stdout
			close(pipe_fd[1]);
			run_cmd(cmd_data, env);
			print_error_msg_and_exit(ERR_UNKNOWN);
		}
		else if (in_or_out == OUTPUT)
		{
			fprintf(stderr, "execute with out file\n");
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

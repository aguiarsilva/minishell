
#include "lib/minishell.h"

// will be moved out of main
int	main(int argc, char *argv[], char *env[])
{
	pid_t	process_id;
	char	*space;
	char	*temp;
	char	*cmd;
	bool	buildin; // something like that to determine if a normal cmd or build in is called

	space = " ";
	temp = ft_strjoin(argv[1], space);
	cmd = ft_strjoin(temp, argv[2]);
	buildin = true;
	free(temp);

	process_id = fork();
	if (process_id < 0)
	{
		free(cmd);
		print_error_msg_and_exit(ERR_FORK);
	}

	// in childprocess
	if (process_id == 0)
	{
		if (buildin == true)
		{
			run_buildin(cmd, env); // have to allocatestruct before that
		}
		else
		{
			executor(cmd, env);
			print_error_msg_and_exit(ERR_UNKNOWN);
		}
	}
	else
	// {
	// 	// parent process
	// 	wait(NULL);  // Wait for child process to complete
	// 	return 0;
	// }
	{
		free(cmd);
		check_child_status(process_id);
	}

}




#include "lib/minishell.h"

// raw execve
// int	main(void)
// {
//  	pid_t	process_id[2];
//
//  	process_id[0] = fork();
//  	if (process_id[0] < 0)
//  		perror("forked failed");
//
//  	if (process_id[0] == 0)
//  	{
//  		char *argv[] = {"ls", "-l", NULL};
//  		execve("/bin/ls", argv, NULL);
//  		perror("execve");
//  		exit(EXIT_FAILURE);
//  	} else
//  	{
//  		// Parent process
//  		wait(NULL);  // Wait for child process to complete
//  	}
//  	return 0;
//  }

// with child processes
int	main(int argc, char *argv[], char *env[])
{
	pid_t	process_id;
	char	*space;
	char	*cmd;

	space = " ";
	cmd = ft_strjoin(ft_strjoin(argv[1], space), argv[2]);

	process_id = fork();
	if (process_id < 0)
		exit(EXIT_FAILURE);

	// in childprocess
	if (process_id == 0)
	{
		executor(cmd, env);
		fprintf(stderr, "unreachable");
		exit(EXIT_FAILURE);
	}
	else
	// {
	// 	// parent process
	// 	wait(NULL);  // Wait for child process to complete
	// 	return 0;
	// }
	{
		// if (waitpid(process_id, &exit_status, 0) == -1)
		// 	exit(EXIT_FAILURE);
		//
		// // Check if the child process terminated normally
		// if (WIFEXITED(exit_status))
		// {
		// 	int exit_code = WEXITSTATUS(exit_status);
		// 	printf("Child exited with code %d\n", exit_code);
		// } else if (WIFSIGNALED(exit_status)) {
		// 	int term_signal = WTERMSIG(exit_status);
		// 	printf("Child terminated by signal %d\n", term_signal);
		// } else {
		// 	printf("Child terminated with unknown status\n");
		// }
		check_child_status(process_id);
	}

}


// without childprocesses
// int	main(int argc, char *argv[], char *env[])
// {
// 	char	*space;
// 	char	*cmd;
// 	// fprintf(stderr,"argv [1] = %s\n", argv[1]);
// 	// fprintf(stderr,"argv [2] = %s\n", argv[2]);
//
// 	space = " ";
// 	cmd = ft_strjoin(ft_strjoin(argv[1], space), argv[2]);
// 	fprintf(stderr,"cmd = %s\n", cmd);
// 	executor(cmd, env);
// 	perror("should not reach this \n");
// 	exit(EXIT_FAILURE);
// 	return 0;
// }
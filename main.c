
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
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	// in childprocess
	if (process_id == 0)
	{
		fprintf(stderr,"child process start \n");
		executor(cmd, env);
		fprintf(stderr,"should not reach this \n");
		exit(EXIT_FAILURE);
	}
	else
	{
		// parent process
		fprintf(stderr,"parentprocess start\n");
		wait(NULL);  // Wait for child process to complete
		return 0;
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
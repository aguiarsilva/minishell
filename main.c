
#include "lib/minishell.h"

// will be moved out of main
int	main(int argc, char *argv[], char *env[])
{
	pid_t	process_id;
//	char	*space;
//	char	*temp;
//	char	*cmd;
	t_cmd	*cmd_data;
	char	**input;
	int		i;
//	bool	buildin; // something like that to determine if a normal cmd or build in is called

//	space = " ";
//	temp = ft_strjoin(argv[1], space);
//	cmd = ft_strjoin(temp, argv[2]);
//	buildin = true;
//	free(temp);

	input = safe_malloc(argc * sizeof(char *));
	if (!input)
		return (-1);

	i = 0;
	while (i < argc -1)
	{
		input[i] = ft_strdup(argv[i + 1]);
		printf("input[%d] = %s\n", i, input[i]);
		if (!input[i])
			return (-1);
		i++;
	}
//	int len = strlen(input[1]);
//	printf ("len = %d\n", len);
//	i = 0;
//	while (i < argc)
//	{
//		printf("input[%d] = %s\n", i, input[i]);
//		i++;
//	}
	cmd_data = fill_cmd(input);
	process_id = fork();
	if (process_id < 0)
	{
		free_cmd_data(cmd_data);
		print_error_msg_and_exit(ERR_FORK);
	}

	// in childprocess
	if (process_id == 0)
	{
		if (cmd_data->builtin)
		{
			run_builtin(cmd_data, env);
		}
		else
		{
			executor(cmd_data, env);
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
		free(cmd_data);
		check_child_status(process_id);
	}

}



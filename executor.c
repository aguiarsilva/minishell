
#include "lib/minishell.h"

void executor(char *cmd, char **env)
{
	char	**split_cmd;
	char	*exec_path;

	exec_path = get_exec_path(cmd, env);
	split_cmd = parse_command_with_quotes(cmd);
	printf("Executable Path via printf: %s\n", exec_path);
	fprintf(stderr, "Executable Path: %s\n", exec_path);

	// Print split_cmd array to stderr
	fprintf(stderr, "Command arguments:\n");
	for (int i = 0; split_cmd[i]; i++)
	{
		fprintf(stderr, "split_cmd[%d]: %s\n", i, split_cmd[i]);
	}
	if (execve(exec_path, split_cmd, env) == -1)
	{
		fprintf(stderr, "Error executing %s: %s\n", exec_path, strerror(errno));
		free(exec_path);
		ft_free_array(split_cmd);
		exit(EXIT_FAILURE);
	}
}
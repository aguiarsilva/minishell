#include "../lib/minishell.h"

char* combine_command_and_args(char* cmd, char** args) // temporary
{
	size_t cmd_length = strlen(cmd);
	size_t args_length = 0;
	int i = 0;

	// Calculate total length for args
	while (args && args[i])
	{
		args_length += strlen(args[i]) + 1; // +1 for space
		i++;
	}
	// Allocate memory for combined command
	char* full_cmd = malloc(cmd_length + args_length + 1); // +1 for null terminator
	if (!full_cmd)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	strcpy(full_cmd, cmd);
	i = 0;
	while (args && args[i])
	{
		strcat(full_cmd, " ");
		strcat(full_cmd, args[i]);
		i++;
	}
	return (full_cmd);
}

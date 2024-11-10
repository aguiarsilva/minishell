
#include "../lib/minishell.h"

int	pwd(void)
{
	char	*current_work_directory;

	current_work_directory = getcwd(NULL, 0);
	if (!current_work_directory)
	{
		perror("getcwd");
		free(current_work_directory);
		return (1);
	}
	printf("%s\n", current_work_directory);
	free(current_work_directory);
	return (0);
}

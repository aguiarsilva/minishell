
#include "lib/minishell.h"
// add if for each build ins

int run_buildin(char *cmd, char **env)
{
	int	exit_code;

	exit_code = 0;
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0 && \
			ft_strlen(cmd) == 4)
		exit_code = echo(cmd);
	return (exit_code); // placeholder need to implement echo first
}
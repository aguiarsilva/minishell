
#include "lib/minishell.h"
// add if for each build ins

void run_buildin(char *cmd, char **env)
{
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)) && \
			ft_strlen(cmd) == 4)
	return; // placeholder need to implement echo first
}

#include "../lib/minishell.h"
// add if for each build ins

int	run_builtin(t_cmd *cmd_data, char **env)
{
	int	exit_code;

	exit_code = 0;
	printf("in builtin");
	if (ft_strncmp(cmd_data->cmd, "echo", ft_strlen(cmd_data->cmd)) == 0 && \
			ft_strlen(cmd_data->cmd) == 4)
		exit_code = echo(cmd_data);
	return (exit_code);
}


#include "../lib/minishell.h"
// add if for each build ins

int	run_builtin(t_cmd *cmd_data, t_env *env_list)
{
	int	exit_code;

	exit_code = 0;
	if (ft_strncmp(cmd_data->cmd, "echo", ft_strlen(cmd_data->cmd)) == 0 && \
			ft_strlen(cmd_data->cmd) == 4)
		exit_code = echo(cmd_data);
	else if (ft_strncmp(cmd_data->cmd, "export", ft_strlen(cmd_data->cmd)) == 0 && \
			ft_strlen(cmd_data->cmd) == 6)
		exit_code = export_builtin(cmd_data->args, &env_list);
	return (exit_code);
}


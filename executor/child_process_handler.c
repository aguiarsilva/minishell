
#include "../lib/minishell.h"

void	handle_child_process(t_cmd *cmd_data, char *env[])
{
	if (cmd_data->builtin)
		run_builtin(cmd_data, env);
	else
	{
		executor(cmd_data, env);
		print_error_msg_and_exit(ERR_UNKNOWN);
	}
}

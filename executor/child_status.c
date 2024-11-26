
#include "../lib/minishell.h"

void	check_child_status(pid_t child_pid, t_cmd *cmd_lst)
{
	int	status;
	int	exit_code;
	int	term_signal;

	if (waitpid(child_pid, &status, 0) == -1)
	{
		// printf("waitpid failed for PID %d: %s\n", child_pid, strerror(errno));
		return ;
	}
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		cmd_lst->exit_code = exit_code;
		// fprintf(stderr, "DEBUG: exitcode of cmd %s = %d\n", cmd_lst->cmd,
			// cmd_lst->exit_code);
		// printf("Child process (PID %d) exited with code %d\n",
			// child_pid, exit_code);
	}
	else
	{
		cmd_lst->exit_code = -1;
		// printf("Child process (PID %d) terminated with unknown status\n",
			// child_pid);
	}
}



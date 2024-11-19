
#include "../lib/minishell.h"

void	check_child_status(pid_t child_pid, t_cmd *cmd_lst)
{
	int	status;
	int	exit_code;
	int	term_signal;

	if (waitpid(child_pid, &status, 0) == -1)
	{
		fprintf(stderr, "waitpid failed for PID %d: %s\n", child_pid, strerror(errno));
		return ;
	}
	if (WIFEXITED(status)) //Check if the Child Process Exited Normally
	{
		exit_code = WEXITSTATUS(status);
		cmd_lst->exit_code = exit_code;
		printf("DEBUG check exitcode of cmd %s, %d\n", cmd_lst->cmd, cmd_lst->exit_code);
		printf("Child process (PID %d) exited with code %d\n", child_pid, exit_code);
	}
	else if (WIFSIGNALED(status)) //Check if the Child Process Was Terminated by a Signal
	{
		term_signal = WTERMSIG(status);
		cmd_lst->exit_code = 128 + term_signal; // Set exit_code to signal number + 128 (POSIX convention)
		printf("Child process (PID %d) terminated by signal %d\n", child_pid, term_signal);
	}
	else
	{
		cmd_lst->exit_code = -1; // Unknown or unexpected termination
		printf("Child process (PID %d) terminated with unknown status\n", child_pid);
	}

}



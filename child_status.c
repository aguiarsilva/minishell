
#include "lib/minishell.h"

void check_child_status(pid_t child_pid)
{
	int	status;
	int	exit_code;
	int	term_signal;

	if (waitpid(child_pid, &status, 0) == -1)
	{
		fprintf(stderr, "waitpid failed for PID %d: %s\n", child_pid, strerror(errno));
		return;
	}

	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		printf("Child process (PID %d) exited with code %d\n", child_pid, exit_code);
	} else if (WIFSIGNALED(status))
	{
		term_signal = WTERMSIG(status);
		printf("Child process (PID %d) terminated by signal %d\n", child_pid, term_signal);
	} else
		printf("Child process (PID %d) terminated with unknown status\n", child_pid);
}



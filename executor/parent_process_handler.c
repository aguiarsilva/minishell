
#include "../lib/minishell.h"

void handle_parent_process(pid_t process_id, t_cmd *cmd_data)
{
	// Free the command data in the parent process
	free(cmd_data); // should only free when minishell is exited?

	// Wait for the child process and check its status
	check_child_status(process_id);
}

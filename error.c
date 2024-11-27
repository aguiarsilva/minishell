
#include "lib/minishell.h"

int	print_error_msg(char *error)
{
	write(STDERR_FILENO, error, ft_strlen(error));
	return (1);
}

void	print_error_open_file_and_exit(char *filename, int err_code)
{
	perror(filename);
	exit (err_code);
}

void	print_cmd_not_found_and_exit(char *cmd, char *exec_path, char **env)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found: \n", STDERR_FILENO);
	free(exec_path);
	ft_free_array(env);
	exit(127);
}

//void	print_error_cmd_not_found_and_exit(char *split_cmd)
//{
//	ft_putstr_fd("minishell: ", STDERR_FILENO);
//	ft_putstr_fd("command not found: ", STDERR_FILENO);
//	ft_putstr_fd(split_cmd, STDERR_FILENO); // not 100 % correct yet should only print the command without args
//	ft_putstr_fd("\n", STDERR_FILENO);
//	exit(127);
//}

void	print_custom_msg_and_exit(char *error, int exit_code)
{
	ft_putstr_fd(error, STDOUT_FILENO);
	exit (exit_code);
}

void	print_error_msg_and_exit(char *error)
{
	perror(error);
	exit (EXIT_FAILURE);
}

//void	print_fd_debug(const char *message)
//{
//
//	fprintf(stderr, "DEBUG: %s\n", message);
//
//	// Print the actual fd numbers
//	fprintf(stderr, "DEBUG: stdin(0)=%d, stdout(1)=%d\n",
//			fcntl(STDIN_FILENO, F_GETFL),
//			fcntl(STDOUT_FILENO, F_GETFL));
//
//	// Print where stdin points to
//	char stdin_buf[256];
//	char stdout_buf[256];
//	ssize_t stdin_len = readlink("/proc/self/fd/0", stdin_buf, sizeof(stdin_buf)-1);
//	ssize_t stdout_len = readlink("/proc/self/fd/1", stdout_buf, sizeof(stdout_buf)-1);
//
//	if (stdin_len != -1) {
//		stdin_buf[stdin_len] = '\0';
//		fprintf(stderr, "DEBUG: stdin points to: %s\n", stdin_buf);
//	}
//
//	if (stdout_len != -1) {
//		stdout_buf[stdout_len] = '\0';
//		fprintf(stderr, "DEBUG: stdout points to: %s\n\n", stdout_buf);
//	}
//}
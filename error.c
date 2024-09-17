
#include "lib/minishell.h"

int	print_error_msg(char *error)
{
	write(STDERR_FILENO, error, ft_strlen(error));
	return (1);
}

void	print_error_cmd_not_found_and_exit(char *split_cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putstr_fd(split_cmd, STDERR_FILENO); // not 100 % correct yet should only print the command without args
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(127);
}

void	print_error_open_file_and_exit(char *filename, char *error)
{
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit (EXIT_FAILURE);
}

void	print_error_msg_and_exit(char *error)
{
	perror(error);
	exit (EXIT_FAILURE);
}
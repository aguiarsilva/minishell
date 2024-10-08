#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/ft_printf/get_next_line/get_next_line.h"
# include "executor.h"
# include "parsing.h"
# include "builtins.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define INPUT 1
# define OUTPUT 2
# define NOFILE 3
# define ERR_CMD "minishell: "
# define ERR_FORK "Fork failed."
# define ERR_PIPE "Pipe Error"
# define ERR_IMPOSSIBLE "Impossible stop sabotating my Program :("
# define ERR_UNKNOWN "Unexpected error: execve succeeded but reached the end of executor function"

int		print_error_msg(char *error);
void	print_error_cmd_not_found_and_exit(char *split_cmd);
void	print_error_msg_and_exit(char *error);
void	print_error_open_file_and_exit(char *filename, int err_code);
void	print_error_cmd_arg_not_found_and_exit(char *split_cmd);
// utils.c
void	*safe_malloc(size_t size);
#endif //MINISHELL_H


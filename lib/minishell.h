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
# define ERR_DUP2 "Dup2 failed "
# define ERR_FORK "Fork failed."
# define ERR_PIPE "Pipe Error"
# define ERR_FILE "Error during opening file"
# define ERR_IMPOSSIBLE "Impossible stop sabotating my Program :("
# define ERR_UNKNOWN "Unexpected error: execve succeeded but reached the end of executor function"

// delete not needed fuction later
int		print_error_msg(char *error);
void	print_error_cmd_not_found_and_exit(char *split_cmd);
void	print_error_msg_and_exit(char *error);
void	print_error_open_file_and_exit(char *filename, int err_code);
void	print_error_cmd_arg_not_found_and_exit(char *split_cmd);
void	print_fd_debug(const char *message);
// utils.c
void	*safe_malloc(size_t size);
char	*ft_strncpy(char *dest, const char *src, int n);
char	*ft_strcpy(char *dest, const char *src);
int		ft_strcmp(char *s1, char *s2);
int		ft_isspace(int c);
#endif //MINISHELL_H


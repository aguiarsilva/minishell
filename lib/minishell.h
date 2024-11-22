#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/ft_printf/get_next_line/get_next_line.h"
# include "executor.h"
# include "parsing.h"
# include "builtins.h"
# include "lexer.h"
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
# define HEREDOC_INPUT 4
# define APPEND_OUTPUT 5
# define CMD_NO_ARGUMENTS 0
# define PATH_VALID 0
# define EXPORT 1
# define NO_EXPORT 0
# define ERR_NO_CUR_DIR "cd: error retrieving current directory: getcwd:"
# define ERR_PARENT_DIR_ACCESS " cannot access parent directories: No such file or directory\n"
# define ERR_NO_SUCH_DIR " No such file or directory\n"
# define ERR_CMD "minishell: "
# define ERR_DUP2 "Dup2 failed "
# define ERR_FORK "Fork failed."
# define ERR_PIPE "Pipe Error"
# define ERR_FILE "Error during opening file"
# define ERR_IMPOSSIBLE "Impossible stop sabotating my Program :("
# define ERR_UNKNOWN "Unexpected error: execve succeeded but reached the end of executor function"
# define EXIT_TOO_MANY_ARGS "exit: too many arguments\n"
# define EXIT_NUMERIC_ARG_REQ "exit: numeric argument required\n"

// error.c delete not needed fuction later
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
void	ft_putstr_fd_mod(char *s, int fd);
char	*ft_charjoin_mod(char *s1, char s2);

// printer.c
void	print_env_list_old(t_env *lst);
void	print_env_node(t_env *node);
void	print_token_lst(t_token *token);
void	print_redir_list(t_redir *redir_head);
void	print_cmd(t_cmd *command);

//env_list.c
t_env	*create_env(char **ori_env, char **argv);
// env_list_utils.c
char	**env_list_to_array(t_env *env_list);
void	free_env_node(t_env *node);
void	free_env_list(t_env **env_lst);
char	*get_key_in_env_lst(t_env *env_lst, char *key);
int		set_value_in_env_lst(t_env *env_lst, char *key, char *value);
void	update_env_exit_code(t_env *env_list, char *key, t_cmd *cmd_lst);
void	update_env_exit_code_for_builtins(t_env *env_list, int exit_code);
#endif //MINISHELL_H


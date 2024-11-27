/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:50:27 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/11/26 12:52:09 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/ft_printf/get_next_line/get_next_line.h"
# include "executor.h"
# include "parsing.h"
# include "builtins.h"
# include "lexer.h"
# include "env_lst.h"
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
# define HEREDOC_INPUT 4
# define APPEND_OUTPUT 5
# define CMD_NO_ARGUMENTS 0
# define PATH_VALID 0
# define EXPORT 1
# define NO_EXPORT 0
# define ERR_NO_CUR_DIR "cd: error retrieving current directory: getcwd:"
# define ERR_PARENT_DIR_ACCESS "cannot access directories \n"
# define ERR_NO_SUCH_DIR " No such file or directory\n"
# define ERR_CMD "minishell: "
# define ERR_DUP2 "Dup2 failed "
# define ERR_FORK "Fork failed."
# define ERR_PIPE "Pipe Error"
# define ERR_FILE "Error during opening file"
# define ERR_IMPOSSIBLE "Impossible stop sabotating my Program :("
# define ERR_UNKNOWN " Unexpected error "
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
void	debug_env_list(t_env *env_lst, const char *location);

#endif //MINISHELL_H

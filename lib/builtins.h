/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:16:01 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/11/26 11:48:32 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include <stdbool.h>

typedef struct s_cmd	t_cmd;
typedef struct s_env	t_env;


//builtins_utils.c
int		check_for_builtin(char *cmd);
//cd.c
int		cd_dir(t_cmd *cmd_lst, t_env *env_lst);
//echo.c
int		echo(t_cmd *cmd_data);
//export_builtin.c
int		export_builtin(char **args, t_env **env_list);
//export_builtin_utils.c
bool	handle_no_arguments(t_env **env_list, int arg_count);
bool	is_valid_identifier(const char *key, bool check_first_char);
char	*ft_strndup(const char *s1, size_t n);
int		count_arg_from_args(char **args);
//pwd.c
int		pwd(void);
//env.c
int		env_builtin(t_cmd *cmd_data, t_env *env_lst);
void	print_env_list(t_env *env_lst, bool export);
//unset.c
int		unset_builtin(char **args, t_env **env_lst);
//exit.c
int		is_valid_number(char *str);
int		builtin_exit(t_cmd *cmd, t_env *env);

#endif

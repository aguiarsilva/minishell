
#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
//	int				exit_code;
	struct s_env	*next;
}		t_env;

//builtins_utils.c
int		check_for_builtin(char *cmd);
//cd.c
int		cd_dir(t_cmd *cmd_lst, t_env *env_lst);
//echo.c
int		echo(t_cmd *cmd_data);
//export_builtin.c
int		export_builtin(char **args, t_env **env_list);

//export_builtin.c
bool	is_valid_identifier(const char *key, bool check_first_char);
char	*ft_strndup(const char *s1, size_t n);
//env_utils.c
void	add_or_update_env_var(t_env **env_list, char *key, char *value);
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

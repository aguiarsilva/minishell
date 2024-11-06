
#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	int				exit_code;
	struct s_env	*next;
}		t_env;

//env_list.c
t_env	*create_env(char **ori_env, char **argv);
char	**env_list_to_array(t_env *env_list);
//echo.c
int		echo(t_cmd *cmd_data);
int		check_for_builtin(char *cmd);
//export.c
int 	export_builtin(char **args, t_env **env_list);
int 	is_valid_identifier(const char *key);
int		print_export_error(const char *key);

//env_utils.c
t_env	*find_env_var(t_env *env_list, char *key);
void	add_or_update_env_var(t_env **env_list, char *key, char *value);
void 	print_env_list(t_env *env_list);

#endif

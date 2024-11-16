
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

//builtins_utils.c
int		check_for_builtin(char *cmd);
//cd.c
int		cd_dir(t_cmd *cmd_lst, t_env *env_lst);
//echo.c
int		echo(t_cmd *cmd_data);
//export_buildin.c
int		export_builtin(char **args, t_env **env_list);
bool	is_valid_identifier(const char *key);
int		print_export_error(const char *key);
//env_utils.c
void	add_or_update_env_var(t_env **env_list, char *key, char *value);
//pwd.c
int		pwd(void);
#endif


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
t_env	*create_env(char **ori_env, char *argv[]);
//echo.c
int		echo(t_cmd *cmd_data);
int		check_for_builtin(char *cmd);
#endif

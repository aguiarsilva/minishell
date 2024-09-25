
#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "minishell.h"
// basis struct for testing
/*typedef struct s_cmd
{
	char	*cmd; // echo 
	char	**args; // // -n
	int		builtin;
}	t_cmd;*/
typedef struct s_cmd t_cmd;
typedef struct s_token t_token;


//executor.c
void	executor(t_cmd *cmd_data, char **env);

//exebuildin.c
int		run_builtin(t_cmd *cmd_data, char **env);

//executor_utils.c
char	*get_env_value_by_name(char *envVarName, char **env);
char	**parse_command_with_quotes(char *cmd);
void	ft_free_array(char **array);
char	*get_exec_path(char *cmd, char **env);
void	free_cmd_data(t_cmd *cmd_data);

//child_status.c
void	check_child_status(pid_t child_pid);

//test.c
// t_cmd	*fill_cmd(char **input);
t_cmd *fill_cmd (t_token *words);
char	*combine_command_and_args(char *cmd, char **args); // temporary
#endif //EXECUTOR_H

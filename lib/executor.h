
#ifndef EXECUTOR_H
#define EXECUTOR_H

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
}	t_cmd;

//executor.c
void	executor(char *cmd, char **env);

//exebuildin.c
int		run_buildin(t_cmd *cmd, char **env);

//executorutils.c
char	*get_env_value_by_name(char *envVarName, char **env);
char	**parse_command_with_quotes(char *cmd);
void	ft_free_array(char **array);
char	*get_exec_path(char *cmd, char **env);
//child_status
void	check_child_status(pid_t child_pid);
#endif //EXECUTOR_H

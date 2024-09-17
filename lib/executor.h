
#ifndef EXECUTOR_H
#define EXECUTOR_H

#endif //EXECUTOR_H

//executor.c
void	executor(char *cmd, char **env);

//executorutils.c
char	*get_env_value_by_name(char *envVarName, char **env);
char	**parse_command_with_quotes(char *cmd);
void	ft_free_array(char **array);
char	*get_exec_path(char *cmd, char **env);
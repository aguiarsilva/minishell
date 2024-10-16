
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
typedef struct s_redir t_redir;


//executor.c
void	run_process(t_cmd *cmd_data, char *env[]);
void	run_cmd(t_cmd *cmd_data, char *env[]);

//exebuildin.c
int		run_builtin(t_cmd *cmd_data, char **env);

//executor_utils.c
char	*get_env_value_by_name(char *envVarName, char **env);
char	**parse_command_with_quotes(char *cmd);
void	ft_free_array(char **array);
char	*get_exec_path(char *cmd, char **env);
void	free_cmd_data(t_cmd *cmd_data);
size_t	get_cmd_data_list_size(t_cmd *cmd_data);

//child_status.c
void	check_child_status(pid_t child_pid);

//child_process_handler.c
void	run_builtin_or_execute(t_cmd *cmd_data, char *env[]);

//file_handler.c
int		open_input_or_output_file(char *filename, int in_or_out);

//parent_process_handler.c
void	handle_parent_process(pid_t process_id, t_cmd *cmd_data);
//test.c
// t_cmd	*fill_cmd(char **input);
t_cmd *fill_cmd (t_token *words, t_redir *redir_list);
char	*combine_command_and_args(char *cmd, char **args); // temporary
#endif //EXECUTOR_H


#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "minishell.h"


typedef struct s_cmd	t_cmd;
typedef struct s_token	t_token;
typedef struct s_redir	t_redir;

//process_handler.c
void	run_builtin_or_execute(t_cmd *cmd_data, char *env[]);
void	run_process(t_cmd *cmd_data, char *env[]);

//executor.c
void	run_cmd(t_cmd *cmd_data, char *env[]);

//child_process_handler.c
pid_t	create_child_process(t_cmd *cmd, char *env[], int prev_pipe_fd[2], int pipe_fd[2], int original_stdout);
void	handle_child_process(t_cmd *cmd, char *env[], int prev_pipe_fd[2], int pipe_fd[2], size_t cmd_count);

//pipe_utils.c
void	init_pipe_fds(int pipe_fd[2], int prev_pipe_fd[2]);
void	create_pipe_if_needed(t_cmd *cmd, int pipe_fd[2]);
void	close_pipe_fds(int pipe_fd[2]);
void	update_prev_pipe_fds(int prev_pipe_fd[2], int pipe_fd[2]);

//redirections.c
void	handle_file_redirections(t_cmd *cmd);
void	handle_pipe_redirections(t_cmd *cmd, int prev_pipe_fd[2], int pipe_fd[2], size_t cmd_count);
void	handle_input_redirections(t_cmd *cmd);

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

//parent_process_handler.c
void	handle_parent_exit(pid_t process_id, t_cmd *cmd_data);
void	handle_parent_pipes_and_process(pid_t process_id, t_cmd *cmd, int prev_pipe_fd[2], int pipe_fd[2]);
//test.c
t_cmd	*fill_cmd (t_token *words, t_redir *redir_list);
char	*combine_command_and_args(char *cmd, char **args); // temporary
#endif //EXECUTOR_H

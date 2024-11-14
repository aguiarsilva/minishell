
#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "minishell.h"

typedef struct s_cmd	t_cmd;
typedef struct s_token	t_token;
typedef struct s_redir	t_redir;
typedef struct s_env	t_env;

//process_handler.c
void	run_builtin_or_execute(t_cmd *cmd_lst, t_env **env_lst);
void	run_process(t_cmd *cmd_lst, t_env **env_lst);
//executor.c
void	run_cmd(t_cmd *cmd_data, t_env **env_lst);

//child_process_handler.c
void	handle_child_process(t_cmd *cmd, t_env **env_lst, int prev_pipe_fd[2], int pipe_fd[2], size_t cmd_count);

//execute_heredoc.c
void	handle_heredoc(t_token *cur_token, t_token **next_token,
			t_token **prev_token, int file_type);
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
int		run_builtin(t_cmd *cmd_data, t_env **env_lst);

//executor_utils.c
char	*get_env_value_by_name(char *envVarName, char **env);
char	**parse_command_with_quotes(char *cmd);
void	ft_free_array(char **array);
char	*get_exec_path(char *cmd, char **env);
void	free_cmd_data(t_cmd *cmd_lst);
size_t	get_cmd_lst_size(t_cmd *cmd_data);

//child_status.c
void	check_child_status(pid_t child_pid);

//parent_process_handler.c
void	handle_parent_exit(pid_t process_id, t_cmd *cmd_data);
void	handle_parent_pipes_and_process(pid_t process_id, t_cmd *cmd, int prev_pipe_fd[2], int pipe_fd[2]);

#endif //EXECUTOR_H

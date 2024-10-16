#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include <stdbool.h>

# define RED "\x1b[31m"
# define RESET "\x1b[0m"

extern	int		g_signal;

typedef enum s_type
{
	REDIR_IN = '<', // 60
	REDIR_OUT = '>', // 62
	APPEND = 'A', // 65
	HEREDOC = 'H', // 72
	WORD = 'W', // 87
	PIPE = '|', //124
}	t_type;

typedef struct s_prompt
{
	char	*symbols;
	char	*whitespace;
}	t_prompt;


typedef struct s_redir
{
	char			*file_name;
	t_type			type;
	// char			*delim;
	struct s_redir	*next;
}	t_redir;

typedef struct s_token
{
	char				*val;
	t_type				type;
	//int					idx;
	struct s_token		*next;
}	t_token;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				builtin;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

/*check.c*/
bool	is_quote(char c);
bool	is_redirection_symbol(char c);
char	*verify_syntax(char *str);
int		str_spaces(const char *str);
bool	is_redir_operator(const char *wd);

/*cleanup.c*/
void	free_prompt(t_prompt *prompt);
void    free_mutil_cmd_arr(char **array);
void    free_tk(t_token *tk_list);

/*parsing.c*/
t_token	*make_token(char *wd, t_type type);
t_token	*multi_cmd_init(t_token *new, t_prompt *prompt);
bool	multi_cmd_arr_init(t_token *new, char *cp_val);
const char *get_type_name(t_type type);
t_redir	*create_redir_struct(t_redir **redir_head, t_token *token_node, int filetype);
t_redir	*extract_redirection_list_from_tokens(t_token *token_list);
bool	is_filename(const char *str);

/*prompt_init.c*/
void	init_prompt(t_prompt *prompt);

/*redir_token.c*/
int	flag_heredoc(t_token **tk_lst, t_cmd *new_cmd);
int	flag_redir(t_token **tk_lst, t_cmd *new_cmd);
char	*redir_handling(char *input);

/*redir_utils*/
void	add_file_to_list(t_redir **lst, t_redir *file_name);
t_redir	*create_file(char *delimiter, t_type type, char *file_name);
char	*put_begin_space(char *str, int i);

/*signal_handling.c*/
void	interrupt_signal(int signal);
void	interruption_signal_process(int signal);
void	quit_signal(int signal);
void	signal_setter(void (*past_signal[2])(int));
void	signal_restore(void	(*past_signal[2])(int));

/*token.c*/
char	*ft_strtok(char *str, const char *delim);
size_t	ft_strspn(const char *str, const char *accept);
char	*quoted_str(char *str, const char *delim);
void	remove_quotes(char **str);
char	*ft_strtok_rm_quotes(char *str, const char *delim);
t_type	get_token_type(char *token);
void	assign_token_type(t_token *token_list);

/*utils_list.c*/
// t_token *build_list(t_prompt *prompt, char *msg);
t_token *build_list(char *input, char **env);
void	append_node(t_token **head, t_token **curr, t_token *new);
void	nodes_init(t_token **head, t_token **cur, t_token **new);

/*utils.c*/
char    *ft_strncpy(char *dest, const char *src, int n);
char    *ft_strcpy(char *dest, const char *src);
int ft_strcmp(char *s1, char *s2);
int	ft_isspace(int c);
void add_token_to_list(t_token **head, t_token **tail, t_token *new_token);
t_token *create_append_token(char *input, size_t *i);
t_token *create_redir_out_token(char *input, size_t *i);
t_token *create_heredoc_token(char *input, size_t *i);
t_token *create_redir_in_token(char *input, size_t *i);
t_token *create_pipe_token(char *input, size_t *i);
bool handle_operator(char *input, size_t *i, t_token **head, t_token **tail);
t_token *get_next_token(char *input, size_t *i, bool expect_command);
size_t get_next_token_len(char *input, size_t start);
t_cmd *build_command_list(char *input);
void add_command_to_list(t_cmd **head, t_cmd **tail, t_cmd *new_cmd);
void add_token_to_command(t_cmd *cmd, t_token *token);
char *handle_single_quotes(const char *input, int *i);
char *handle_double_quotes(const char *input, int *i, char **env);
char handle_escape_sequence(const char *input, int *i);
char *handle_env_variable(const char *input, int *i, char **env);


#endif
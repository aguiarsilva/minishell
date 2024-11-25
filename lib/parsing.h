#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include <stdbool.h>

# define BUFFER_SIZE 1024

extern int		g_signal;

typedef enum s_type
{
	REDIR_IN = '<', // 60
	REDIR_OUT = '>', // 62
	APPEND = 'A', // 65
	HEREDOC = 'H', // 72
	WORD = 'W', // 87
	PIPE = '|', //124
	EQUAL = '=',
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
	struct s_redir	*next;
}	t_redir;

typedef struct s_token
{
	char				*val;
	t_type				type;
	bool				eof_flag;
	struct s_token		*next;
}	t_token;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				exit_code;
	int				builtin;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_lexer
{
	t_token	*head;
	t_token	*tail;
	char	buffer[1024];
	int		buf_index;
	bool	quoted;
}	t_lexer;

typedef struct s_buffer_state {
    char buffer[BUFFER_SIZE];
    size_t buf_index;
    int was_quoted;
    int in_quotes;
} t_buffer_state;

typedef struct s_token_list {
    t_token *head;
    t_token *tail;
} t_token_list;

typedef struct s_parser_context {
    t_buffer_state *state;
    t_token_list *tokens;
    t_env **env_lst;
} t_parser_context;

typedef struct s_char_context {
    const char *input;
    size_t current_index;
    size_t input_length;
} t_char_context;

//build_lst.c
t_token	*build_lst(char *input, t_env **lst);
void	add_new_token_to_lst(t_token **head, t_token **tail,
			t_token *new_token);

/*check.c*/
bool	is_redirection_symbol(char c);
char	*verify_syntax(char *str);
int		str_spaces(const char *str);
bool	is_redir_operator(const char *wd);

/*cleanup.c*/
void	free_prompt(t_prompt *prompt);
void	free_mutil_cmd_arr(char **array);
void	free_tk(t_token *tk_list);

//parsing.c
t_cmd	*fill_cmd_lst(t_token *token_list, t_redir *redir_list);

//parsing_utils.c
t_cmd	*create_new_cmd_node(char *token_val, t_redir *redir_list);
void	add_new_cmd_to_cmd_lst(t_cmd **head, t_cmd **tail, t_cmd *new_cmd);
bool	is_skippable_token(t_token *prev, t_token *cur);
size_t	count_arguments(t_token *token_list);
bool	is_special_command(char *cmd);
//parsing_free.c
void	free_cmd_list(t_cmd *head);
void	cleanup_args(char **args, int count);
t_cmd	*cleanup_cmd_list(t_cmd *head);
/*prompt_init.c*/
void	init_prompt(t_prompt *prompt);

//redir_struct.c
void	add_to_redir_lst(t_token *cur_token, t_redir **redir_lst,
			int file_type, t_token *prev_token);
//redir_process.c
t_redir	*create_redir_lst_from_tokens(t_token *token_lst);
//redir_utils.c
t_redir	*get_last_redirection_node(t_redir *redir_head);
bool	is_filename(const char *str);
bool	is_file_without_extension(t_token *prev_token, t_token *cur_token);
int		determine_redirection_type(int filetype);
int		determine_file_type(t_token *cur_token);

/*signal_handling.c*/
void	interrupt_signal(int signal);
//void	interruption_signal_process(int signal);
void	quit_signal(int signal);
void	signal_setter(void (**past_signal)(int));
void	signal_restore(void	(**past_signal)(int));

//check_syntax.c
bool	is_valid_redirection_syntax(t_token *token_list);

/*token.c*/
char	*ft_strtok(char *str, const char *delim);
size_t	ft_strspn(const char *str, const char *accept);
char	*quoted_str(char *str, const char *delim);
char	*ft_strtok_rm_quotes(char *str, const char *delim);
bool	is_quote(char c);

////build_lst_utils.c nothing used
//void	process_pipe(t_token** head, t_token** tail, int* i);
//void	process_quotes(char* input, size_t* i, char* buffer, int* buf_index);
//void	process_escape_sequence(char* input, size_t *i, char* buffer, int* buf_index);
//// void	process_env_variable(char* input, int* i, char* buffer, int* buf_index);
//void	process_regular_text(char *input, size_t *i, char *buffer, int *buf_index);
////build_lst_utils2.c
//bool	is_quoted(char* input);
//void	append_node(t_token** head, t_token** curr, t_token* new);
//void	nodes_init(t_token** head, t_token** cur, t_token** new);
//int		skip_whitespace(char *input, int i, int len);

////handle_operator_utils.c
//t_token	*create_append_token(size_t *i);
//t_token	*create_redir_out_token(void);
//t_token	*create_heredoc_token(size_t *i);
//t_token	*create_redir_in_token(void);
//t_token	*create_pipe_token(void);

/*handle_quotes.c*/
char	*handle_single_quotes(char *input, size_t *i);
char	*handle_double_quotes(char *input, size_t *i);
char	handle_escape_sequence(char *input, size_t *i, bool interpret);
char	*handle_env_variable(char *input, size_t *i);
void	remove_quotes(char *str, int *was_quoted);

/*handle_quotes_utils.c*/
char	get_interpreted_escape_char(char *input, size_t *i);
void	process_character(char *input, size_t *i, char *buffer, int *buf_index);
void	process_env_variable(char* input, size_t* i, char* buffer, int* buf_index);
//expand_utils.c
char	*get_exit_code_value(t_env *env_lst);
char	*append_remainder(char *base, char *remainder);
bool	is_valid_env_char(char next_char);
bool	is_var_delimiter(char c);
int		calculate_brace_offset(char *split, int start, int *i);
//check_expand.c
char	*expand_word(char *word, int i, t_env *env_lst);
char	*create_fake_pid(int *i);
//expander.c
int		expand_to_str(char *str_to_expand, int *i, char **exp_word, t_env *env_lst);
//t_token *split_into_words(char *input);

#endif
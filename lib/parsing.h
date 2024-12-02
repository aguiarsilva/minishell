/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:49:22 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/12/01 09:26:48 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include <stdbool.h>

# define BUFFER_SIZE 1024

extern int		g_signal;

typedef enum s_type
{
	REDIR_IN = '<',
	REDIR_OUT = '>',
	APPEND = 'A',
	HEREDOC = 'H',
	WORD = 'W',
	PIPE = '|',
}	t_type;

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

typedef struct s_buffer_state
{
	char	buffer[BUFFER_SIZE];
	size_t	buf_index;
	int		was_quoted;
	int		in_quotes;
	char	quote_type;
	bool	should_expand;
}	t_buffer_state;

typedef struct s_token_list
{
	t_token	*head;
	t_token	*tail;
}	t_token_list;

typedef struct s_parser_context
{
	t_buffer_state	*state;
	t_token_list	*tokens;
	t_env			**env_lst;
}	t_parser_context;

typedef struct s_char_context
{
	const char	*input;
	size_t		current_index;
	size_t		input_length;
}	t_char_context;

typedef struct s_parser_data
{
	t_buffer_state		state;
	t_token_list		tokens;
	t_parser_context	ctx;
	t_char_context		char_ctx;
	int					is_escaped;
	char				current_quote;
}	t_parser_data;

//build_lst.c
t_token	*build_lst(char *input, t_env **lst);
void	add_new_token_to_lst(t_token **head, t_token **tail,
			t_token *new_token);
//check_expand.c
char	*expand_word(char *word, int i, t_env *env_lst);
char	*create_fake_pid(int *i);
//check_syntax.c
bool	is_valid_redirection_syntax(t_token *token_list);
//expand_utils.c
char	*get_exit_code_value(t_env *env_lst);
char	*append_remainder(char *base, char *remainder);
bool	is_valid_env_char(char next_char);
bool	is_var_delimiter(char c);
int		calculate_brace_offset(char *split, int start, int *i);
//expander.c
int		expand_to_str(char *str_to_expand, int *i,
			char **exp_word, t_env *env_lst);
//parsing.c
t_cmd	*fill_cmd_lst(t_token *token_list, t_redir *redir_list);
t_token	*find_next_pipe_symbol(t_token *token_list);
t_cmd	*create_cmd_from_tokens(t_token *token_list,
			t_redir *cur_redir,
			t_cmd **head, t_cmd **tail);
//parsing_free.c
void	free_cmd_list(t_cmd *head);
void	cleanup_args(char **args, int count);
t_cmd	*cleanup_cmd_list(t_cmd *head);
void	free_all(t_cmd *cmd_head, t_env **env_head);
void	free_redir_list(t_redir *redir_list);
//parsing_free2.c
void	free_tk(t_token *tk_list);
//parsing_utils.c
t_cmd	*create_new_cmd_node(char *token_val, t_redir *redir_list);
void	add_new_cmd_to_cmd_lst(t_cmd **head, t_cmd **tail, t_cmd *new_cmd);
bool	is_skippable_token(t_token *prev, t_token *cur);
size_t	count_arguments(t_token *token_list);
bool	is_special_command(char *cmd);
//redir_copy_utils
t_redir	*deep_copy_redir_list(t_redir *original);
int		create_and_link_cmd(t_token *token_list, t_redir *cur_redir,
			t_cmd **head, t_cmd **tail);
void	advance_lists_after_pipe(t_token **token_list, t_redir **cur_redir);
//redir_process.c
t_redir	*create_redir_lst_from_tokens(t_token *token_lst);
//redir_struct.c
void	add_to_redir_lst(t_token *cur_token, t_redir **redir_lst,
			int file_type, t_token *prev_token);
void	append_redir_node(t_redir **redir_lst, t_redir **last_redir,
			t_redir *new_redir);
t_redir	*check_if_token_need_redir(t_token **token_list, t_token *cur_token,
			t_redir *cur_redir);
//redir_utils.c
t_redir	*get_last_redirection_node(t_redir *redir_head);
bool	is_filename(const char *str);
bool	is_file_without_extension(t_token *prev_token, t_token *cur_token);
int		determine_redirection_type(int filetype);
int		determine_file_type(t_token *cur_token);
//signal_handling.c
void	sig_int(int signal);
void	sig_int_in_process(int signal);
void	sig_quit(int signal);
void	set_signals(void (*old_signal[2])(int));
void	restore_signals(void (*old_signal[2])(int));

#endif
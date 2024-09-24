#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

# define RED "\x1b[31m"
# define RESET "\x1b[0m"

extern	int		g_signal;

typedef enum s_type
{
	START,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	SIMPLE_CMD,
	BUILTIN_CMD,
	ARGS,
	FILE_EOF
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
	char			*val;
	char			**multi_cmd;
	struct s_token	*next;
	int				count_cmd;
	int				count_wd;
	t_redir			*redir;
}	t_token;

/*check.c*/
bool	is_quote(char c);
bool	is_redirection_symbol(char c);
char	*verify_syntax(char *str);
int		str_spaces(const char *str);
bool    is_redir_operator(const char *wd);

/*cleanup.c*/
void	free_prompt(t_prompt *prompt);
void    free_mutil_cmd_arr(char **array);
void    free_tk(t_token *tk_list);

/*parsing.c*/
t_token	*make_token(char *wd);
t_token	*multi_cmd_init(t_token *new, t_prompt *prompt);
bool	multi_cmd_arr_init(t_token *new, char *cp_val);

/*prompt_init.c*/
void	init_prompt(t_prompt *prompt);

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
char	remove_quotes(char **str);
char	*ft_strtok_rm_quotes(char *str, const char *delim);

/*utils_list.c*/
t_token *build_list(t_prompt *prompt, char *msg);
void	append_node(t_token **head, t_token **curr, t_token *new);
void	nodes_init(t_token **head, t_token **cur, t_token **new);

/*utils.c*/
char    *ft_strncpy(char *dest, const char *src, int n);
char    *ft_strcpy(char *dest, const char *src);
int ft_strcmp(char *s1, char *s2);


#endif
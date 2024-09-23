#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

# define RED "\x1b[31m"
# define RESET "\x1b[0m"

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
	char			**multi_command;
	struct s_token	*next;
	int				count_cmd;
	int				count_word;
}	t_token;

/*check.c*/
bool	is_quote(char c);
bool	is_redirection_symbol(char c);
char	*verify_syntax(char *str);
int		str_spaces(const char *str);

/*cleanup.c*/
void	free_prompt(t_prompt *prompt);

/*prompt_init.c*/
void	init_prompt(t_prompt *prompt);

/*token.c*/
char	*ft_strtok(char *str, const char *delim);
size_t	ft_strspn(const char *str, const char *accept);
char	*quoted_str(char *str, const char *delim);
char	remove_quotes(char **str);
char	*ft_strtok_remove_quotes(char *str, const char *delim);

/*utils_list.c*/
t_token *build_list(t_prompt *prompt, char *msg);
void	append_node(t_token **head, t_token **curr, t_token *new);
void	nodes_init(t_token **head, t_token **cur, t_token **new);

/*utils.c*/
char    *ft_strncpy(char *dest, const char *src, int n);
char    *ft_strcpy(char *dest, const char *src);


#endif
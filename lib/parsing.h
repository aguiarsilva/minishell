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

#endif
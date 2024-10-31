
#ifndef LEXER_H
#define LEXER_H

# include "minishell.h"
# include <stdbool.h>

typedef struct s_cmd	t_cmd;
typedef struct s_token	t_token;
typedef struct s_redir	t_redir;

//lexer.c
t_type	get_token_type(char *token);
void	assign_token_type(t_token *token_list);

//lexer_utils.c
t_type	get_token_type(char *token);

#endif //LEXER_H
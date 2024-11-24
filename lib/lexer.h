
#ifndef LEXER_H
#define LEXER_H

# include "minishell.h"

typedef struct s_cmd	t_cmd;
typedef struct s_token	t_token;
typedef struct s_redir	t_redir;
typedef struct s_lexer	t_lexer;
//lexer.c
t_type	get_token_type(char *token);
void	assign_token_type(t_token *token_list);
t_token	*create_word_list(char *input, t_env **env_lst);

//lexer_utils.c
t_type	get_token_type(char *token);

#endif //LEXER_H
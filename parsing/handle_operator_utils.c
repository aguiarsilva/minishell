

#include "../lib/minishell.h"

t_token* create_append_token(char* input, size_t* i)
{
	t_token* new_token = make_token(">>", APPEND);
	(*i)++; // Skip the second '>'
	return new_token;
}

t_token* create_redir_out_token(char* input, size_t* i)
{
	return make_token(">", REDIR_OUT);
}

t_token* create_heredoc_token(char* input, size_t* i)
{
	t_token* new_token = make_token("<<", HEREDOC);
	(*i)++; // Skip the second '<'
	return new_token;
}

t_token* create_redir_in_token(char* input, size_t* i)
{
	return make_token("<", REDIR_IN);
}

t_token* create_pipe_token(char* input, size_t* i)
{
	return make_token("|", PIPE);
}
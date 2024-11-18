

#include "../lib/minishell.h"

// Helper function to process pipe tokens
//void	process_pipe(t_token **head, t_token **tail, int *i)
//{
//	t_token	*pipe_token;
//
//	pipe_token = make_token("|", PIPE, env_lst);
//	add_new_token_to_lst(head, tail, pipe_token);
//	(*i)++;
//}

// Helper function to process quoted strings
void	process_quotes(char *input, int *i, char *buffer, int *buf_index)
{
	char	quote_type = input[*i];
	char*	quote_content;

	if (quote_type == '\'')
	{
		fprintf(stderr, "single quote if \n");
		quote_content = handle_single_quotes(input, i);
	}
	else // double quote
	{
		fprintf(stderr, "double quote if \n");
		quote_content = handle_double_quotes(input, i);
	}

	if (quote_content)
	{
		ft_strcpy(buffer + *buf_index, quote_content);
		*buf_index += ft_strlen(quote_content);
		free(quote_content);
	}
}

// Helper function to process escape sequences
void	process_escape_sequence(char* input, int* i, char* buffer, int* buf_index)
{
	fprintf(stderr, "double slash if \n");
	buffer[(*buf_index)++] = handle_escape_sequence(input, i, false);

	while (*i < ft_strlen(input) && !ft_isspace(input[*i]) &&
		  input[*i] != '|' && input[*i] != '\'' &&
		  input[*i] != '"' && input[*i] != '\\' &&
		  input[*i] != '$')
	{
		buffer[*buf_index] = input[*i];
		(*buf_index)++;
		(*i)++;
	}
}
// Helper function to process environment variables
void	process_env_variable(char* input, int* i, char* buffer, int* buf_index)
{
	fprintf(stderr, "$ if \n");
	char* env_var;

	env_var = handle_env_variable(input, i);
	if (env_var)
	{
		ft_strcpy(buffer + *buf_index, env_var);
		*buf_index += strlen(env_var);
	}
}
// Helper function to process regular text

void	process_regular_text(char *input, int *i, char *buffer, int *buf_index)
{
	while (*i < ft_strlen(input) && !ft_isspace(input[*i])
		&& input[*i] != '|' && input[*i] != '"'
		&&input[*i] != '$')
	{
		buffer[*buf_index] = input[*i];
		(*buf_index)++;
		(*i)++;
	}
}

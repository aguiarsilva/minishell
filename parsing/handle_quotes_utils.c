#include "../lib/minishell.h"

// void process_env_variable(const char* input, int* i, char* buffer, int* buf_index)
// {
// 	char* env_var;
//
// 	while (input[*i] == '$')
// 	{
// 		env_var = handle_env_variable(input, i);
// 		while (env_var)
// 		{
// 			ft_strcpy(&buffer[*buf_index], env_var);
// 			*buf_index += ft_strlen(env_var);
// 			free(env_var);
// 			break;
// 		}
// 		break;
// 	}
// }
//

void process_character(char* input, size_t *i, char* buffer, int* buf_index)
{
	while (input[*i] == '\\')
	{
		buffer[*buf_index] = handle_escape_sequence(input, i, false);
		(*buf_index)++;
		break;
	}
	while (input[*i] != '\\' && input[*i] != '$')
	{
		buffer[*buf_index] = input[*i];
		(*i)++;
		(*buf_index)++;
		break;
	}
}

char	get_interpreted_escape_char(char *input, size_t *i)
{
	char escape_char;

	escape_char = input[*i];
	while (escape_char == 'n' || escape_char == 't' || escape_char == '\\')
	{
		(*i)++;
		while (escape_char == 'n')
			return '\n';
		while (escape_char == 't')
			return '\t';
		while (escape_char == '\\')
			return '\\';
	}
	return '\\';
}

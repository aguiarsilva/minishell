#include "../lib/minishell.h"

char	*handle_single_quotes(char *input, size_t *i)
{
//	int start;// not used only set
	char *buffer;  
	int buf_index;

//	start = ++(*i); // Skip the opening single quote
	buffer = malloc(1024); // Buffer to store the result
	buf_index = 0;
	while (input[*i] != '\'' && input[*i] != '\0')
		buffer[buf_index++] = input[(*i)++]; // Loop until the closing single quote
	if (input[*i] == '\'')
		(*i)++;	// If a closing quote was found, skip it
	buffer[buf_index] = '\0';  // Null-terminate the buffer
	return buffer;  // Return the string inside single quotes
}

char *handle_double_quotes(char *input, size_t *i)
{
    char *buffer;
    int buf_index;
    
    (*i)++;  // Skip opening quote
    buffer = malloc(1024);
    buf_index = 0;
    while (input[*i] != '"' && input[*i] != '\0')
    {
        while (input[*i] == '$')
        {
            process_env_variable(input, i, buffer, &buf_index);
            break;
        }
        while (input[*i] != '$')
        {
            process_character(input, i, buffer, &buf_index);
            break;
        }
    }
    while (input[*i] == '"')
        (*i)++;
    buffer[buf_index] = '\0';
    return buffer;
}

/*char	*handle_double_quotes(const char *input, int *i)
{
	int start;  // Skip the opening double quote
	char *buffer;  // Buffer to store the result
	int buf_index;
	char *env_var;

	start = ++(*i);
	buffer = malloc(1024);
	buf_index = 0;
	while (input[*i] != '"' && input[*i] != '\0')
	{
		if (input[*i] == '\\')
			buffer[buf_index++] = handle_escape_sequence(input, i, false); // Handle escape sequences
		else if (input[*i] == '$')
		{ // Handle environment variables
			env_var = handle_env_variable(input, i);
			if (env_var)
			{
				ft_strcpy(&buffer[buf_index], env_var);
				buf_index += ft_strlen(env_var);
				free(env_var);
			}
		}
		else
			buffer[buf_index++] = input[(*i)++]; // Normal character
	}
	if (input[*i] == '"')
		(*i)++;	// Skip the closing double quote
	buffer[buf_index] = '\0'; // Null-terminate the buffer
	return buffer; // Return the string inside double quotes
}*/

// char handle_escape_sequence(const char *input, int *i)
// {
//     if (input[*i] == '\\') {
//         (*i)++; // Move past the backslash
//         if (input[*i] == 'n') {
//             (*i)++;
//             return '\n'; // Return newline character
//         } else if (input[*i] == 't') {
//             (*i)++;
//             return '\t'; // Return tab character
//         } else if (input[*i] == '\\') {
//             (*i)++;
//             return '\\'; // Return a literal backslash
//         }
//         // Return the next character as-is if not a recognized escape sequence
//         return input[(*i)++];
//     }
//     return input[(*i)++]; // If not an escape sequence, return the current character
// }

#include <stdio.h>
#include <stdbool.h>

// Updated handle_escape_sequence to handle printing of escape characters
char handle_escape_sequence(char *input, size_t *i, bool interpret)
{
    char current_char;
    
	current_char = input[*i];
    while (current_char == '\\')
    {
        (*i)++;
        while (interpret)
            return get_interpreted_escape_char(input, i);
        return '\\';
    }
    
    (*i)++;
    return current_char;
}

char *handle_env_variable(char *input, size_t *i)
{
	char var_name[100];
	int var_index;

	var_index = 0;
	(*i)++;  // Skip the '$' symbol
	while (ft_isalnum(input[*i]) || input[*i] == '_')  // Parse variable name
		var_name[var_index++] = input[(*i)++];
	var_name[var_index] = '\0';  // Null-terminate the variable name
	fprintf(stderr, "var_name: %s\n", var_name);
	// Fetch the variable value from the environment
	char *var_value = getenv(var_name);
	fprintf(stderr, "var_value: %s\n", var_value);
	return (var_value ? var_value : "");  // Return the value or an empty string if not found
}

// void remove_quotes(char *str, int *was_quoted) {
//     int i, j;
//     int in_quotes = 0;
//     char quote_type = 0;
    
//     if (!str) return;
//     *was_quoted = 0;  // Initialize to not quoted
    
//     for (i = 0, j = 0; str[i] != '\0'; i++) {
//         if ((str[i] == '"' || str[i] == '\'') && (!in_quotes || quote_type == str[i])) {
//             *was_quoted = 1;  // Mark that this string was quoted
//             if (!in_quotes) {
//                 in_quotes = 1;
//                 quote_type = str[i];
//             } else {
//                 in_quotes = 0;
//                 quote_type = 0;
//             }
//             continue;
//         }
//         str[j++] = str[i];
//     }
//     str[j] = '\0';
// }

static void handle_escape_char(char *buffer, size_t *i, size_t *new_index)
{
    if (buffer[*i] == '\\')
    {
        if (buffer[*i + 1] == 'n')
        {
            buffer[*new_index] = 'n';
            (*i)++;
        }
        else if (buffer[*i + 1] == 't')
        {
            buffer[*new_index] = 't';
            (*i)++;
        }
        else if (buffer[*i + 1] == '\\')
        {
            buffer[*new_index] = '\\';
            (*i)++;
        }
        else
            buffer[*new_index] = buffer[*i];
    }
    else
        buffer[*new_index] = buffer[*i];
}

void remove_quotes(char *buffer, int *was_quoted)
{
    size_t i = 0;
    size_t new_index = 0;
    int in_quotes = 0;
    char quote_type = 0;

    while (buffer[i])
    {
        if ((buffer[i] == '"' || buffer[i] == '\'') && !in_quotes)
        {
            in_quotes = 1;
            quote_type = buffer[i];
            *was_quoted = 1;
            i++;
            continue;
        }
        else if (buffer[i] == quote_type && in_quotes)
        {
            in_quotes = 0;
            quote_type = 0;
            i++;
            continue;
        }
        
        // Handle escaped characters inside double quotes
        if (in_quotes && quote_type == '"' && buffer[i] == '\\' && buffer[i + 1])
        {
            handle_escape_char(buffer, &i, &new_index);
            i++;
            new_index++;
            continue;
        }
        
        buffer[new_index++] = buffer[i++];
    }
    buffer[new_index] = '\0';
}
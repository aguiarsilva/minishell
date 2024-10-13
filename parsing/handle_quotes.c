#include "../lib/minishell.h"

char *handle_single_quotes(const char *input, int *i) {
    int start = ++(*i);  // Skip the opening single quote
    char *buffer = malloc(1024);  // Buffer to store the result
    int buf_index = 0;

    while (input[*i] != '\'' && input[*i] != '\0') {  // Loop until the closing single quote
        buffer[buf_index++] = input[(*i)++];
    }

    if (input[*i] == '\'') {  // If a closing quote was found, skip it
        (*i)++;
    }

    buffer[buf_index] = '\0';  // Null-terminate the buffer
    return buffer;  // Return the string inside single quotes
}

char *handle_double_quotes(const char *input, int *i, char **env) {
    int start = ++(*i);  // Skip the opening double quote
    char *buffer = malloc(1024);  // Buffer to store the result
    int buf_index = 0;

    while (input[*i] != '"' && input[*i] != '\0') {
        if (input[*i] == '\\') { // Handle escape sequences
            buffer[buf_index++] = handle_escape_sequence(input, i);
        } else if (input[*i] == '$') { // Handle environment variables
            char *env_var = handle_env_variable(input, i, env);
            if (env_var) {
                strcpy(&buffer[buf_index], env_var);
                buf_index += strlen(env_var);
                free(env_var);
            }
        } else {
            buffer[buf_index++] = input[(*i)++]; // Normal character
        }
    }

    if (input[*i] == '"') { // Skip the closing double quote
        (*i)++;
    }
    buffer[buf_index] = '\0'; // Null-terminate the buffer
    return buffer; // Return the string inside double quotes
}

char handle_escape_sequence(const char *input, int *i) {
    if (input[*i] == '\\') {
        (*i)++; // Move past the backslash
        if (input[*i] == 'n') {
            (*i)++;
            return '\n'; // Return newline character
        } else if (input[*i] == 't') {
            (*i)++;
            return '\t'; // Return tab character
        } else if (input[*i] == '\\') {
            (*i)++;
            return '\\'; // Return a literal backslash
        }
        // Return the next character as-is if not a recognized escape sequence
        return input[(*i)++];
    }
    return input[(*i)++]; // If not an escape sequence, return the current character
}

char *handle_env_variable(const char *input, int *i, char **env)
{
    char var_name[100];
    int var_index = 0;

    (*i)++;  // Skip the '$' symbol
    while (ft_isalnum(input[*i]) || input[*i] == '_')  // Parse variable name
        var_name[var_index++] = input[(*i)++];

    var_name[var_index] = '\0';  // Null-terminate the variable name

    // Fetch the variable value from the environment
    char *var_value = getenv(var_name);
    return (var_value ? var_value : "");  // Return the value or an empty string if not found
}
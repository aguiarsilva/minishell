#include "../lib/minishell.h"

char *remove_surrounding_quotes(char *input_word)
{
    char *result_word;

    // Check if the input word starts with a double quote
    if (input_word[0] == '"')
        result_word = ft_strtrim(input_word, "\""); // Trim double quotes
    // Check if the input word starts with a single quote
    else if (input_word[0] == '\'')
        result_word = ft_strtrim(input_word, "'"); // Trim single quotes
    else
        return (input_word); // Return the input as is if no quotes

    // Handle memory allocation failure for the trimmed word
    if (!result_word)
        return (free(input_word), NULL); // Free input and return NULL if allocation fails

    free(input_word); // Free the original input word after trimming
    return (result_word); // Return the trimmed word
}

int		validate_brackets_parenthesis(char *input_str, int begin, int *i)
{
	int	delim_check;

	delim_check = 0;
	if ((input_str[begin] == '{' && input_str[*i] == '}')
		|| (input_str[begin] == '(' && input_str[*i] == ')'))
	{
		delim_check++;
		(*i)++;
	}
	if (input_str[begin + 1] == '{')
	{
		delim_check = -1;
		ft_putstr_fd("Error: Invalid syntax near '{'. \
			Missing or mismatched closing delimiter.\n", 2);
	}
	return (delim_check);
}

char *strip_quotes(char *input_string, int current_index, int output_index)
{
    int character_count;
    char quote_char;
    char *output_string;

    quote_char = '\0';
    
    // If the input string starts with a single or double quote, return a duplicate of it
    if (input_string[0] == '\'' || input_string[0] == '\"')
        return (ft_strdup(input_string));

    // Count the number of characters excluding quotes
    character_count = count_rm_quotes(input_string);
    
    // If the count is -1, return a duplicate of the original input
    if (character_count == -1)
        return (ft_strdup(input_string));

    // Allocate memory for the output string
    output_string = ft_calloc(character_count + 1, sizeof(char));
    if (!output_string)
        return (NULL); // Return NULL on allocation failure

    // Process the input string to copy characters without quotes
    while (input_string[current_index])
    {
        // If we encounter a quote character, skip it and copy until we find the closing quote
        if (input_string[current_index] == '\'' || input_string[current_index] == '\"')
        {
            quote_char = input_string[current_index++];
            while (input_string[current_index] && input_string[current_index] != quote_char)
                output_string[output_index++] = input_string[current_index++];
        }
        else
        {
            output_string[output_index++] = input_string[current_index]; // Copy character if not a quote
        }
        if (input_string[current_index])
            current_index++; // Move to the next character
    }
    return (output_string); // Return the final string without quotes
}

int count_characters_excluding_quotes(char *input_string)
{
    int character_count;
    char quote_char;
    int current_index;

    current_index = 0;
    character_count = ft_strlen(input_string);
    quote_char = '\0';
	while (input_string[current_index])
    {
        // Check for single or double quote characters
        if (input_string[current_index] == '\'' || input_string[current_index] == '\"')
        {
            quote_char = input_string[current_index++];
            character_count -= 2; // Reduce count for the opening and closing quotes
            // Skip characters until we find the matching quote
            while (input_string[current_index] && input_string[current_index] != quote_char)
                current_index++;
            // If no closing quote is found, return -1 to indicate an error
            if (!input_string[current_index])
                return (-1);
        }
        // Move to the next character
        if (input_string[current_index])
            current_index++;
    }
    return character_count; // Return the final count excluding quotes
}

int valid_variable_char(char c) 
{
    return !(ft_isspace(c) || c == '"' || c == '\'' || c == '}' || c == ')' ||
            c == ':' || c == '=' || c == '^' || c == '%' || (c >= '+' && c <= '/'));
}

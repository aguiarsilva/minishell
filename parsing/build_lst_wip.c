

#include "../lib/minishell.h"

// Helper function to create and add token if buffer is not empty
static void create_token_if_needed(t_token** head, t_token** tail, char* buffer, int buf_index)
{
	if (buf_index > 0)
	{
		buffer[buf_index] = '\0';
		t_token* new_token = make_token(buffer, WORD);
		if (new_token)
		{
			add_new_token_to_lst(head, tail, new_token);
		}
	}
}

// Initialize lexer state
static void	init_lexer_data(t_lexer *lexer_data, char *input)
{
	lexer_data->head = NULL;
	lexer_data->tail = NULL;
	lexer_data->buf_index = 0;
	lexer_data->quoted = is_quoted(input);
}

static void process_equal(char* input, int* i, char* buffer, int* buf_index)
{
	fprintf(stderr, "called process_equal");
}

bool is_variable_assignment(const char* input) {
	// Skip leading whitespace
	while (isspace(*input)) {
		input++;
	}
	printf("Input after trimming leading whitespace: '%s'\n", input);

	// Check if the first characters are a valid variable name
	bool is_valid_var = true;
	for (int i = 0; input[i] != '\0' && input[i] != '='; i++) {
		if (!isalnum(input[i]) && input[i] != '_') {
			printf("Character '%c' is invalid for a variable name.\n", input[i]);
			is_valid_var = false;
			break;
		}
	}
	printf("is_valid_var after checking variable name: %s\n", is_valid_var ? "true" : "false");

	// Check if the next character is an equal sign
	int input_len = strlen(input);
	if (is_valid_var == false || input_len < 2 || input[input_len - 1] == '"' || input[input_len - 2] != '=') {
		// printf("Failed condition for equal sign or quotes. Details:\n");
		// printf(" - is_valid_var: %s\n", is_valid_var ? "true" : "false");
		// printf(" - Last character: '%c'\n", input[input_len - 1]);
		// printf(" - Second to last character: '%c'\n", input[input_len - 2]);
		printf("Returning true (1).\n");
		return true;
	}

	// // Check if the value is enclosed in quotes
	// const char* value = strchr(input, '=') + 2;
	// const char* end = input + input_len - 1;
	// printf("Value portion after '=': '%s'\n", value);
	// printf("Expected last character (end): '%c'\n", *end);
	//
	// if (*value != '"' || *end != '"') {
	// 	printf("Failed condition for enclosed quotes around value.\n");
	// 	printf(" - First character of value: '%c'\n", *value);
	// 	printf(" - Last character of value: '%c'\n", *end);
	// 	printf("Returning false (2).\n");
	// 	return false;
	// }

	printf("false.\n");
	return false;
}

char	*ft_charjoin_mod(char *s1, char s2)
{
	char	*ret;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s1) + 1;
	ret = malloc((len + 1) * sizeof(*ret));
	if (!ret)
		return (free(s1), NULL);
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i++] = s2;
	ret[i] = '\0';
	free(s1);
	return (ret);
}

static void process_token(t_lexer *lexer_data, char *input, int *i, int len)
{
	char	*current;
	int j =0;

	lexer_data->buf_index = 0;
	current = &input[*i];
	fprintf(stderr, "input is: %s\n", input);
	fprintf(stderr, "current is: %c\n", *current);

	bool is_env_var = is_variable_assignment(input);
	// while (current[j])
	// {
	// 	if (current[j] == '=' && is_env_var == true)
	// 	{
	// 		printf("detected sign\n");
	// 	}
	// 	j++;
	// }
	if (is_env_var) {
		// Allocate memory for the new string (add space for an extra character if needed)
		char *modified_input = malloc(strlen(input) + 2);  // +2 for potential extra space and null terminator
		int k = 0; // index for modified_input

		while (current[j] != '\0')
		{
			// If we find '=', insert a space before it in modified_input
			if (current[j] == '=') {
				modified_input[k++] = ' ';  // Add space before '='
				printf("Detected '=' and added space before it.\n");
			}
			modified_input[k++] = current[j++];
		}
		modified_input[k] = '\0';  // Null-terminate the new string

		// Print or use modified_input as needed
		fprintf(stderr, "Modified input: %s\n", modified_input);

		// Don't forget to free the memory when done with modified_input
		// free(modified_input);
		current = &modified_input[*i];
	}

	if (*current == '|')
	{
		fprintf(stderr, "pipe if\n");
		process_pipe(&lexer_data->head, &lexer_data->tail, i);
	}

	else if (*current == '=')
	{
		process_equal(input, i, lexer_data->buffer, &lexer_data->buf_index);
		fprintf(stderr, "called process_equal\n");
		(*i)++;
		return ;
	}
	else if (*current == '\'' || *current == '"')
	{
		fprintf(stderr, "quotes\n");
		process_quotes(input, i, lexer_data->buffer, &lexer_data->buf_index);
	}

	else if (*current == '\\' && lexer_data->quoted)
	{
		fprintf(stderr, "escape sequence\n");
		process_escape_sequence(input, i, lexer_data->buffer, &lexer_data->buf_index);
	}

	else if (*current == '$')
	{
		fprintf(stderr, "$ sequence\n");
		process_env_variable(input, i, lexer_data->buffer, &lexer_data->buf_index);
	}

	else
	{
		fprintf(stderr, "called process_regular_text\n");
		process_regular_text(input, i, lexer_data->buffer, &lexer_data->buf_index);
	}

	create_token_if_needed(&lexer_data->head, &lexer_data->tail, lexer_data->buffer, lexer_data->buf_index);
}

t_token *build_lst(char *input, t_env *env_lst)
{
	t_lexer	lexer_data;
	int		i;
	int		len;

	init_lexer_data(&lexer_data, input);
	len = ft_strlen(input);
	i = 0;
	while (i < len)
	{
		i = skip_whitespace(input, i, len);
		if (i >= len)
			break;
		process_token(&lexer_data, input, &i, len);
	}
	return (lexer_data.head);
}
// // Main token builder function
// t_token*	build_lst(char* input, t_env* env_lst)
// {
//     t_token* head = NULL;
//     t_token* tail = NULL;
//     int i = 0;
//     int len = ft_strlen(input);
//     char buffer[1024];
//     int buf_index = 0;
//     bool quoted_string = is_quoted(input);
//
//     while (i < len)
//     {
//         // Skip whitespace
//         while (i < len && ft_isspace(input[i]))
//             i++;
//         if (i >= len)
//             break;
//
//         // Reset buffer for new token
//         buf_index = 0;
//
//         // Process different token types
//         if (input[i] == '|')
//             process_pipe(&head, &tail, &i);
//         else if (input[i] == '\'' || input[i] == '"')
//             process_quotes(input, &i, buffer, &buf_index);
//         else if (input[i] == '\\' && quoted_string)
//             process_escape_sequence(input, &i, buffer, &buf_index);
//         else if (input[i] == '$')
//             process_env_variable(input, &i, buffer, &buf_index);
//         else
//             process_regular_text(input, &i, buffer, &buf_index);
//
//         create_token_if_needed(&head, &tail, buffer, buf_index);
//     }
//     return (head);
// }

// t_token*	build_list(char* input, t_env *env_lst) // working version
// {
// 	t_token* head = NULL;
// 	t_token* tail = NULL;
// 	int i = 0;
// 	int len = ft_strlen(input);
// 	char buffer[1024]; // Buffer to store current token
// 	int buf_index = 0;
// 	bool quoted_string = false;
//
// 	quoted_string = is_quoted(input);
// 	// fprintf(stderr, "The value of bool flag is: %s\n", quoted_string ? "true" : "false");
// 	while (i < len)
// 	{
// 		// Skip whitespace
// 		while (i < len && ft_isspace(input[i]))
// 		{
// 			i++;
// 		}
// 		if (i >= len)
// 		{
// 			break; // Break if we reach the end
// 		}
//
// 		// Check for pipes
// 		if (input[i] == '|')
// 		{
// 			t_token* pipe_token = make_token("|", PIPE);
// 			add_token_to_list(&head, &tail, pipe_token);
// 			i++;
// 			continue; // Expect new command after pipe
// 		}
//
// 		buf_index = 0; // Reset buffer index for new token
//
// 		// Handle quotes
// 		if (input[i] == '\'')
// 		{
// 			fprintf(stderr, "single quote if \n");
// 			char* quote_content = handle_single_quotes(input, &i);
// 			if (quote_content)
// 			{
// 				ft_strcpy(buffer + buf_index, quote_content);
// 				buf_index += ft_strlen(quote_content);
// 				free(quote_content);
// 			}
// 		}
// 		else if (input[i] == '"')
// 		{
// 			fprintf(stderr, "double quote if \n");
// 			char* quote_content = handle_double_quotes(input, &i);
// 			if (quote_content)
// 			{
// 				ft_strcpy(buffer + buf_index, quote_content);
// 				buf_index += ft_strlen(quote_content);
// 				free(quote_content);
// 			}
// 		}
// 		else if (input[i] == '\\' && quoted_string == true)
// 		{
// 			fprintf(stderr, "double slash if \n");
// 			// Collect escape sequences
// 			buffer[buf_index++] = handle_escape_sequence(input, &i, false);
// 			while (i < len && !ft_isspace(input[i]) && input[i] != '|' &&
// 				input[i] != '\'' && input[i] != '"' && input[i] != '\\' && input[i] != '$')
// 			{
// 				buffer[buf_index++] = input[i++];
// 			}
// 		}
// 		else if (input[i] == '$')
// 		{
// 			fprintf(stderr, "$ if \n");
// 			char* env_var = handle_env_variable(input, &i);
// 			if (env_var)
// 			{
// 				ft_strcpy(buffer + buf_index, env_var);
// 				buf_index += strlen(env_var);
// 				// free(env_var); // should not be freed because its a static string and no malloc was used
// 			}
// 		}
// 		else
// 		{
// 			while (i < len && !ft_isspace(input[i]) && input[i] != '|' &&
// 				input[i] != '"' && input[i] != '$')
// 			{
// 				buffer[buf_index++] = input[i++];
// 			}
// 		}
//
// 		buffer[buf_index] = '\0'; // Null-terminate the buffer
//
// 		// If the buffer is not empty, create a token
// 		if (buf_index > 0)
// 		{
// 			t_token* new_token = make_token(buffer, WORD);
// 			if (new_token)
// 			{
// 				add_token_to_list(&head, &tail, new_token);
// 			}
// 		}
// 	}
//
// 	return head;
// }



bool handle_operator(char* input, size_t* i, t_token** head, t_token** tail)
{
	t_token* new_token = NULL;

	if (input[*i] == '|')
		new_token = create_pipe_token(input, i);
	else if (input[*i] == '>' && input[*i + 1] == '>')
		new_token = create_append_token(input, i);
	else if (input[*i] == '>')
		new_token = create_redir_out_token(input, i);
	else if (input[*i] == '<' && input[*i + 1] == '<')
		new_token = create_heredoc_token(input, i);
	else if (input[*i] == '<')
		new_token = create_redir_in_token(input, i);
	if (new_token)
	{
		add_new_token_to_lst(head, tail, new_token);
		(*i)++; // Move to the next character after processing the operator
		return (true); // Indicate that an operator was handled
	}
	return (false); // No operator was handled
}


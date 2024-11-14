

#include "../lib/minishell.h"

// Helper function to create and add token if buffer is not empty
static void	create_token_if_needed(t_token **head, t_token **tail, char *buffer, int buf_index)
{
	t_token* new_token;
	if (buf_index > 0)
	{
		buffer[buf_index] = '\0';
		new_token = make_token(buffer, WORD);
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

static void	process_token(t_lexer *lexer_data, char *input, int *i, int len)
{
	char	*current;

	lexer_data->buf_index = 0;
	current = &input[*i];
	if (*current == '|')
		process_pipe(&lexer_data->head, &lexer_data->tail, i);
	else if (*current == '\'' || *current == '"')
		process_quotes(input, i, lexer_data->buffer, &lexer_data->buf_index);
	else if (*current == '\\' && lexer_data->quoted)
		process_escape_sequence(input, i, lexer_data->buffer, &lexer_data->buf_index);
	else if (*current == '$')
		process_env_variable(input, i, lexer_data->buffer, &lexer_data->buf_index);
	else
		process_regular_text(input, i, lexer_data->buffer, &lexer_data->buf_index);
	create_token_if_needed(&lexer_data->head, &lexer_data->tail, lexer_data->buffer, lexer_data->buf_index);
}

t_token *build_lst(char *input, t_env *env_lst) {
    t_token *word_list = create_word_list(input);
    assign_token_type(word_list);
    return word_list;
}

/*t_token	*build_lst(char *input, t_env *env_lst)
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
}*/
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



//bool	handle_operator(char *input, size_t *i, t_token **head, t_token **tail) // not used????
//{
//	t_token	*new_token;
//
//	new_token = NULL;
//
//	if (input[*i] == '|')
//		new_token = create_pipe_token();
//	else if (input[*i] == '>' && input[*i + 1] == '>')
//		new_token = create_append_token(i);
//	else if (input[*i] == '>')
//		new_token = create_redir_out_token();
//	else if (input[*i] == '<' && input[*i + 1] == '<')
//		new_token = create_heredoc_token(i);
//	else if (input[*i] == '<')
//		new_token = create_redir_in_token();
//	if (new_token)
//	{
//		add_new_token_to_lst(head, tail, new_token);
//		(*i)++; // Move to the next character after processing the operator
//		return (true); // Indicate that an operator was handled
//	}
//	return (false); // No operator was handled
//}


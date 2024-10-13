#include "../lib/minishell.h"

// t_token	*build_list(t_prompt *prompt, char *msg)
// {
// 	t_token	*head;
// 	t_token	*new;
// 	t_token	*curr;
// 	char	*store_prompt_msg;
// 	char	*token;

// 	store_prompt_msg = ft_strdup(msg);
// 	token = ft_strtok(store_prompt_msg, "|");
// 	nodes_init(&head, &curr, &new);
// 	while (token != NULL)
// 	{
// 		new = make_token(token);
// 		if (new == NULL)
// 		{
// 			free_list_of_token(new);
// 			return (NULL);
// 		}
// 		append_node(&head, &curr, new);
// 		multi_cmd_init(new, prompt);
// 		make_redir_list(new, prompt, token);
// 		token = ft_strtok(NULL, "|");
// 	}
// 	free(store_prompt_msg);
// 	return (head);
// }

// // Function to build a list of tokens from a space-separated string
// t_token *build_list(char *input) {
//     t_token *head = NULL;   // Head of the linked list
//     t_token *tail = NULL;   // Tail to keep track of the last token
//     char *token;            // Pointer to hold each token
//     const char delimiter[] = " "; // Token delimiter

//     // Step 1: Tokenize the input string
//     token = strtok(input, delimiter);
//     while (token != NULL) {
//         // Step 2: Create a new token structure
//         t_type  token_type = get_token_type(token);
//         t_token *new_token = make_token(token, token_type); // Change TYPE_1 as needed
//         if (new_token == NULL) {
//             // Handle memory allocation failure
//             // Free the already allocated tokens
//             while (head != NULL) {
//                 t_token *temp = head;
//                 head = head->next;
//                 free(temp->val);
//                 free(temp);
//             }
//             return NULL;
//         }

//         // Step 3: Add the new token to the linked list
//         if (head == NULL) {
//             head = new_token; // If list is empty, set head
//             tail = new_token; // Tail also points to the first token
//         } else {
//             tail->next = new_token; // Link the new token
//             tail = new_token;        // Update the tail to the new token
//         }

//         // Get the next token
//         token = strtok(NULL, delimiter);
//     }

//     return head; // Return the head of the linked list
// }
int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

t_token *build_list(char *input, char **env) {
    t_token *head = NULL;
    t_token *tail = NULL;
    int i = 0;
    int len = ft_strlen(input);
    char buffer[1024];  // Buffer to store current token
    int buf_index = 0;

    while (i < len) {
        // Skip whitespace
        while (i < len && ft_isspace(input[i])) {
            i++;
        }
        if (i >= len) {
            break; // Break if we reach the end
        }

        // Check for pipes
        if (input[i] == '|') {
            t_token *pipe_token = make_token("|", PIPE);
            add_token_to_list(&head, &tail, pipe_token);
            i++;
            continue; // Expect new command after pipe
        }

        buf_index = 0; // Reset buffer index for new token

        // Handle quotes
        if (input[i] == '\'') {
            char *quote_content = handle_single_quotes(input, &i);
            if (quote_content) {
                ft_strcpy(buffer + buf_index, quote_content);
                buf_index += ft_strlen(quote_content);
                free(quote_content);
            }
        } else if (input[i] == '"') {
            char *quote_content = handle_double_quotes(input, &i, env);
            if (quote_content) {
                ft_strcpy(buffer + buf_index, quote_content);
                buf_index += ft_strlen(quote_content);
                free(quote_content);
            }
        } else if (input[i] == '\\') {
            // Collect escape sequences
            buffer[buf_index++] = handle_escape_sequence(input, &i);
        } else if (input[i] == '$') {
            char *env_var = handle_env_variable(input, &i, env);
            if (env_var) {
                ft_strcpy(buffer + buf_index, env_var);
                buf_index += strlen(env_var);
                free(env_var);
            }
        } else {
            // Collect normal characters for the token
            while (i < len && !ft_isspace(input[i]) && input[i] != '|' &&
                   input[i] != '\'' && input[i] != '"' && input[i] != '\\' && input[i] != '$') {
                buffer[buf_index++] = input[i++];
            }
        }

        buffer[buf_index] = '\0'; // Null-terminate the buffer

        // If the buffer is not empty, create a token
        if (buf_index > 0) {
            t_token *new_token = make_token(buffer, WORD);
            if (new_token) {
                add_token_to_list(&head, &tail, new_token);
            }
        }
    }

    return head;
}

void add_token_to_list(t_token **head, t_token **tail, t_token *new_token) 
{
    if (*head == NULL) {
        *head = new_token;
        *tail = new_token;
    } else {
        (*tail)->next = new_token;
        *tail = new_token;
    }
}

void	append_node(t_token **head, t_token **curr, t_token *new)
{
	if (*head == NULL)
	{
		*head = new;
		*curr = new;
	}
	else
	{
		(*curr)->next = new;
		*curr = new;
	}
}

void	nodes_init(t_token **head, t_token **cur, t_token **new)
{
	*head = NULL;
	*cur = NULL;
	*new = NULL;
}

t_token *create_append_token(char *input, size_t *i) 
{
    t_token *new_token = make_token(">>", APPEND);
    (*i)++;  // Skip the second '>'
    return new_token;
}

t_token *create_redir_out_token(char *input, size_t *i) 
{
    return make_token(">", REDIR_OUT);
}

t_token *create_heredoc_token(char *input, size_t *i) 
{
    t_token *new_token = make_token("<<", HEREDOC);
    (*i)++;  // Skip the second '<'
    return new_token;
}

t_token *create_redir_in_token(char *input, size_t *i) 
{
    return make_token("<", REDIR_IN);
}

t_token *create_pipe_token(char *input, size_t *i) 
{
    return make_token("|", PIPE);
}

bool handle_operator(char *input, size_t *i, t_token **head, t_token **tail) {
    t_token *new_token = NULL;

    if (input[*i] == '|' ) {
        new_token = create_pipe_token(input, i);
    } else if (input[*i] == '>' && input[*i + 1] == '>') {
        new_token = create_append_token(input, i);
    } else if (input[*i] == '>') {
        new_token = create_redir_out_token(input, i);
    } else if (input[*i] == '<' && input[*i + 1] == '<') {
        new_token = create_heredoc_token(input, i);
    } else if (input[*i] == '<') {
        new_token = create_redir_in_token(input, i);
    }

    if (new_token) {
        add_token_to_list(head, tail, new_token);
        (*i)++;  // Move to the next character after processing the operator
        return true;  // Indicate that an operator was handled
    }

    return false;  // No operator was handled
}

t_token *get_next_token(char *input, size_t *i, bool expect_command) {
    while (input[*i] && ft_isspace(input[*i])) {
        (*i)++;
    }

    size_t token_len = get_next_token_len(input, *i);
    if (token_len == 0)
        return NULL; // No valid token found

    char *token_str = ft_substr(input, *i, token_len);
    t_type token_type; 

    // Set token_type based on whether a command is expected
    if (expect_command) {
        token_type = WORD; // Treat as command if expected
    } else {
        token_type = get_token_type(token_str); // Otherwise, determine token type
    }

    *i += token_len; // Move past the token in the input
    return make_token(token_str, token_type);
}

size_t get_next_token_len(char *input, size_t start) {
    size_t i = start;
    
      // Skip whitespace characters
    while (input[i] && ft_isspace(input[i])) {
        i++;
    }
    // Handle operators (|, >>, <<, etc.)
    if (input[i] == '|' || input[i] == '<' || input[i] == '>') {
        if ((input[i] == '>' && input[i + 1] == '>') || (input[i] == '<' && input[i + 1] == '<')) {
            return 2; // Handle multi-character operators (>>, <<)
        }
        return 1; // Single character operators (|, <, >)
    }

    // Handle regular words or quoted strings
    while (input[i] && !ft_isspace(input[i]) && input[i] != '|' && input[i] != '>' && input[i] != '<') {
        // If we encounter a quoted string, skip to the matching quote
        if (input[i] == '\'' || input[i] == '"') {
            char quote = input[i];
            i++;
            while (input[i] && input[i] != quote) {
                i++;
            }
            if (input[i]) {
                i++; // Move past the closing quote
            }
        } else {
            i++;
        }
    }

    return i - start;
}

t_cmd *build_command_list(char *input) {
    t_cmd *head = NULL;
    t_cmd *tail = NULL;
    size_t i = 0;
    size_t len = ft_strlen(input);
    bool expect_command = true; // Initially expect a command

    t_cmd *current_cmd = NULL;

    while (i < len) {
        // Skip whitespace
        while (i < len && ft_isspace(input[i])) {
            i++;
        }
        if (i >= len) break; // Break if we reach the end

        // Check for pipe
        if (input[i] == '|') {
            // If a command was being built, finalize it
            if (current_cmd) {
                // Add the command to the list
                add_command_to_list(&head, &tail, current_cmd);
                current_cmd = NULL; // Reset current command
            }
            i++; // Move past the pipe
            expect_command = true; // Expect a new command
            continue; // Go to the next iteration
        }

        // Get the next token
        t_token *new_token = get_next_token(input, &i, expect_command);
        if (new_token) {
            if (!current_cmd) {
                current_cmd = malloc(sizeof(t_cmd)); // Allocate new command
                current_cmd->args = NULL; // Initialize args to NULL
                current_cmd->next = NULL; // Initialize next to NULL
            }
            // Add token to the current command arguments
            add_token_to_command(current_cmd, new_token);
            expect_command = false; // Now we expect more arguments or a pipe
        }
    }

    // Finalize the last command if it exists
    if (current_cmd) {
        add_command_to_list(&head, &tail, current_cmd);
    }

    return head; // Return the head of the command list
}

void add_command_to_list(t_cmd **head, t_cmd **tail, t_cmd *new_cmd) {
    if (*head == NULL) {
        *head = new_cmd;
        *tail = new_cmd;
    } else {
        (*tail)->next = new_cmd;
        *tail = new_cmd;
    }
}

void add_token_to_command(t_cmd *cmd, t_token *token) {
    // Add the token value to the command arguments
    size_t arg_count = 0; // Count existing arguments
    while (cmd->args && cmd->args[arg_count]) {
        arg_count++;
    }
    cmd->args = realloc(cmd->args, sizeof(char *) * (arg_count + 2)); // Resize for new arg + NULL
    cmd->args[arg_count] = token->val; // Assign token value
    cmd->args[arg_count + 1] = NULL; // Null terminate
}

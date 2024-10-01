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

t_token *build_list(char *input) {
    t_token *head = NULL;
    t_token *tail = NULL;
    size_t i = 0;
    size_t len = ft_strlen(input);
    bool expect_command = true;

    while (i < len) {
        while (i < len && ft_isspace(input[i])) {
            i++;
        }
        if (i >= len)
            break;

        if (handle_operator(input, &i, &head, &tail)) {
            expect_command = true;  // After a pipe, expect a new command
            continue;
        }

        t_token *new_token = get_next_token(input, &i, expect_command);
        if (new_token)
        {
                add_token_to_list(&head, &tail, new_token);
                expect_command = false; // Reset to false after first word in the command
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
        return NULL;
    char *token_str = ft_substr(input, *i, token_len);
    t_type token_type; // Declare token_type

    // Use if statement instead of a ternary operator
    if (expect_command) {
        token_type = WORD; // Assign WORD if expect_command is true
    } else {
        token_type = get_token_type(token_str); // Otherwise, get the token type
    }

    *i += token_len;
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

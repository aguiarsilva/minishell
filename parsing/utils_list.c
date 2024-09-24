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

// Function to build a list of tokens from a space-separated string
t_token *build_list(char *input) {
    t_token *head = NULL;   // Head of the linked list
    t_token *tail = NULL;   // Tail to keep track of the last token
    char *token;            // Pointer to hold each token
    const char delimiter[] = " "; // Token delimiter

    // Step 1: Tokenize the input string
    token = strtok(input, delimiter);
    while (token != NULL) {
        // Step 2: Create a new token structure
        t_token *new_token = make_token(token); // Change TYPE_1 as needed
        if (new_token == NULL) {
            // Handle memory allocation failure
            // Free the already allocated tokens
            while (head != NULL) {
                t_token *temp = head;
                head = head->next;
                free(temp->val);
                free(temp);
            }
            return NULL;
        }

        // Step 3: Add the new token to the linked list
        if (head == NULL) {
            head = new_token; // If list is empty, set head
            tail = new_token; // Tail also points to the first token
        } else {
            tail->next = new_token; // Link the new token
            tail = new_token;        // Update the tail to the new token
        }

        // Get the next token
        token = strtok(NULL, delimiter);
    }

    return head; // Return the head of the linked list
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

#include "../lib/minishell.h"

// Function to free a command list in case of an error
static void	free_cmd_list(t_cmd* head)
{
	t_cmd	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->cmd);
		free(temp->args);
		free(temp);
	}
}

// Function to create and initialize a new command
t_cmd*	create_new_cmd_node(char* token_val, t_redir* redir_list)
{
	t_cmd	*cmd_list_node;

	cmd_list_node = safe_malloc(sizeof(t_cmd));
	if (cmd_list_node == NULL)
		return (NULL);
	cmd_list_node->cmd = ft_strdup(token_val); // Duplicate the command string
	if (cmd_list_node->cmd == NULL)
	{
		free(cmd_list_node);
		return (NULL);
	}
	cmd_list_node->redir = redir_list;
	cmd_list_node->next = NULL;
	cmd_list_node->builtin = check_for_builtin(cmd_list_node->cmd);
	return (cmd_list_node);
}

// Function to count the number of arguments in the token list (up to a pipe)
static size_t	count_arguments(t_token *token_list)
{
	size_t		arg_count;
	t_token*	cur;

	arg_count = 0;
	cur = token_list;
	while (cur != NULL && cur->type != PIPE)
	{
		if (get_token_type(cur->val) == WORD)
			arg_count++;
		cur = cur->next;
	}
	return (arg_count);
}

// Check if token should be skipped
bool	is_skippable_token(t_token* prev, t_token* cur)
{
	// No previous token, can't be a redirection file
	if (prev == NULL)
		return (false);

	// Not a redirection token
	if (prev->type != REDIR_OUT && prev->type != REDIR_IN)
		return (false);

	// Not a word token (potential filename)
	if (get_token_type(cur->val) != WORD)
		return (false);

	// If we've reached here, it's a redirection file
	return (true);
}

void	cleanup_args(char** args, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(args[i]);
		i++;
	}
	free(args);
}


// Process a single token into args array
int	process_token(t_cmd* cmd_data, t_token* cur, int* arg_index)
{
	if (get_token_type(cur->val) != WORD)
		return (1);

	cmd_data->args[*arg_index] = ft_strdup(cur->val);
	if (!cmd_data->args[*arg_index])
		return (0);  // Allocation failed

//	ft_printf(stderr, "Copied arg: %s\n", cmd_data->args[*arg_index]); // broken print
	(*arg_index)++;
	return (1);
}

// Main argument filling function
int fill_arguments(t_cmd* cmd_data, t_token* token_list, size_t arg_count)
{
	int arg_index = 0;
	t_token* cur = token_list;
	t_token* prev = NULL;

	// Allocate args array
	cmd_data->args = malloc((arg_count + 1) * sizeof(char*));
	if (!cmd_data->args)
		return -1;

	// Process tokens
	while (cur && cur->type != PIPE) {
		// Skip certain tokens
		if (is_skippable_token(prev, cur)) {
			prev = cur;
			cur = cur->next;
			continue;
		}

		// Try to process current token
		if (!process_token(cmd_data, cur, &arg_index)) {
			cleanup_args(cmd_data->args, arg_index);
			return -1;
		}

		prev = cur;
		cur = cur->next;
	}

	// Null-terminate args array
	cmd_data->args[arg_index] = NULL;
	return 0;
}

// Main function to parse the token list and fill the command structure
t_cmd*	fill_cmd(t_token *token_list, t_redir *redir_list)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*cmd_data;
	size_t	arg_count;

	head = NULL;
	tail = NULL;
	// Start parsing the token list
	while (token_list != NULL)
	{
		if (token_list->type != WORD)
		{
			fprintf(stderr, "Error: First token is not a command (WORD)\n");
			free_cmd_list(head);
			return NULL;
		}

		// Create a new command node
		cmd_data = create_new_cmd_node(token_list->val, redir_list);
		if (!cmd_data)
		{
			free_cmd_list(head);
			return NULL;
		}

		// Count the arguments for this command
		arg_count = count_arguments(token_list->next);
		// Fill the arguments for the command
		if (fill_arguments(cmd_data, token_list->next, arg_count) < 0)
		{
			free_cmd_list(head);
			return (NULL);
		}

		// Add the command to the command list
		if (head == NULL)
		{
			head = cmd_data; // Set head if list is empty
			tail = cmd_data; // Initialize tail
		}
		else
		{
			tail->next = cmd_data; // Link the new command
			tail = cmd_data; // Update tail
		}

		// Move to the next token (after the pipe if it exists)
		t_token* cur = token_list->next;
		while (cur != NULL && cur->type != PIPE)
			cur = cur->next;
		if (cur != NULL && cur->type == PIPE)
			token_list = cur->next;
		else
			break; // Exit if no more commands
	}
	return (head); // Return the head of the command list
}

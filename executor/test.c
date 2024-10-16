#include "../lib/minishell.h"

// Function to free a command list in case of an error
void free_cmd_list(t_cmd* head)
{
	while (head != NULL)
	{
		t_cmd* temp = head;
		head = head->next;
		free(temp->cmd);
		free(temp->args);
		free(temp);
	}
}

// Function to create and initialize a new command
t_cmd* create_new_cmd_node(char* token_val, t_redir* redir_list)
{
	t_cmd*	cmd_list_node;

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
	return (cmd_list_node);
}

// Function to count the number of arguments in the token list (up to a pipe)
size_t count_arguments(t_token* token_list)
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

// Function to fill the arguments array for a command
int fill_arguments(t_cmd* cmd_data, t_token* token_list, size_t arg_count)
{
	size_t i = 0;
	t_token* cur = token_list;
	t_token* prev = NULL; // Keep track of the previous token

	// Allocate space for arguments (+1 for NULL terminator)
	cmd_data->args = safe_malloc((arg_count + 1) * sizeof(char*));
	if (!cmd_data->args)
		return (-1);

	// Populate the arguments array
	while (cur != NULL && cur->type != PIPE)
	{
		// Skip the current token if the previous token was a REDIR_IN and the current one is a WORD
		if (prev != NULL && prev->type == REDIR_OUT && get_token_type(cur->val) == WORD)
		{
			// Just skip this argument (it's the file name after the '<' redirection)
			prev = cur;
			cur = cur->next;
			continue;
		}

		// If it's a WORD token, copy it to the args array
		if (get_token_type(cur->val) == WORD)
		{
			cmd_data->args[i] = ft_strdup(cur->val);
			printf("cmd_data_args copied: %s\n", cmd_data->args[i]);
			if (!cmd_data->args[i])
			{
				while (i > 0)
				{
					free(cmd_data->args[--i]);
				}
				free(cmd_data->args);
				return -1;
			}
			i++;
		}
		// Move to the next token, updating `prev` and `cur`
		prev = cur;
		cur = cur->next;
	}
	cmd_data->args[i] = NULL; // Null-terminate the args array
	return (0);
}


// Main function to parse the token list and fill the command structure
t_cmd* fill_cmd(t_token* token_list, t_redir* redir_list)
{
	t_cmd* head = NULL; // Head of the command list
	t_cmd* tail = NULL; // Tail of the command list
	t_cmd* cmd_data;
	size_t arg_count;

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
		printf("argcount %ld\n", arg_count);
		// Fill the arguments for the command
		if (fill_arguments(cmd_data, token_list->next, arg_count) < 0)
		{
			free_cmd_list(head);
			return NULL;
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


char* combine_command_and_args(char* cmd, char** args) // temporary
{
	size_t cmd_length = strlen(cmd);
	size_t args_length = 0;
	int i = 0;

	// Calculate total length for args
	while (args && args[i])
	{
		args_length += strlen(args[i]) + 1; // +1 for space
		i++;
	}
	// Allocate memory for combined command
	char* full_cmd = malloc(cmd_length + args_length + 1); // +1 for null terminator
	if (!full_cmd)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	strcpy(full_cmd, cmd);
	i = 0;
	while (args && args[i])
	{
		strcat(full_cmd, " ");
		strcat(full_cmd, args[i]);
		i++;
	}
	return (full_cmd);
}

#include "../lib/minishell.h"

// t_cmd *fill_cmd(char **input) // need to rework to work with multiple cmds
// {
// 	t_cmd	*cmd_data;
// 	size_t	arg_count; // will get it from struct later
// 	size_t	i;

// 	cmd_data = safe_malloc(sizeof(t_cmd));
// 	if (!cmd_data)
// 		return (NULL);
// 	cmd_data->cmd = ft_strdup(input[0]);

// 	arg_count = 0;
// 	while (input[arg_count])
// 		arg_count++;
// //	fprintf(stderr,"arg_count =%d\n", arg_count);
// 	cmd_data->args = safe_malloc(sizeof(char *) * arg_count);
// 	i = 0;
// 	while (i < arg_count)
// 	{
// //		fprintf(stderr,"in while \n");
// //		fprintf(stderr,"%s\n", input[i]);
// 		cmd_data->args[i] = ft_strdup(input[i]);
// //		fprintf(stderr,"%s\n", cmd_data->args[i]);
// 		i++;
// 	}
// //	fprintf(stderr,"test %s\n", cmd_data->args[2]);
// 	cmd_data->args[arg_count] = NULL;
// 	cmd_data->builtin = check_for_builtin(cmd_data->cmd);
// 	return (cmd_data);
// }

// t_cmd	*fill_cmd (t_token *list) // currently only handles a single command // working version
// {
// 	t_cmd	*cmd_data;
// 	t_token	*cur;
// 	size_t	i;
// 	size_t	arg_count;
// 	t_token	*tmp;
//
// 	i = 0;
// 	arg_count = 0;
// 	cmd_data = safe_malloc(sizeof(t_cmd));
// 	if (!cmd_data)
// 		return (NULL);
// 	cmd_data->cmd = ft_strdup(list->val);
// 	cur = list->next;
// 	tmp = cur;
// 	while (tmp != NULL)
// 	{
// 		arg_count++;
// 		tmp = tmp->next;
// 	}
// 	cmd_data->args = safe_malloc((arg_count + 1) * sizeof(char *));
// 	if (!cmd_data->args)
// 		return (NULL);
// 	while (cur != NULL)
// 	{
// 		cmd_data->args[i] = ft_strdup(cur->val);
// 		cur = cur->next;
// 		i++;
// 	}
// 	cmd_data->args[i] = NULL;
// 	cmd_data->builtin = check_for_builtin(cmd_data->cmd);
// 	return (cmd_data);
// }

// t_cmd* fill_cmd(t_token* token_list, t_redir* redir_list) // prev working version without splitting in smaller functions
// {
// 	t_cmd*	head = NULL; // Head of the command list
// 	t_cmd*	tail = NULL; // Tail of the command list
// 	t_cmd*	cmd_data; // Current command being filled
// 	size_t	i;
// 	size_t	arg_count;
// 	char	*token_val;
// 	t_token	*cur;
//
// 	// Start parsing the token list
// 	while (token_list != NULL)
// 	{
// 		// Allocate memory for a single new command node
// 		cmd_data = safe_malloc(sizeof(t_cmd));
// 		if (!cmd_data)
// 		{
// 			// Free all previously allocated commands if allocation fails
// 			while (head != NULL)
// 			{
// 				t_cmd* temp = head;
// 				head = head->next;
// 				free(temp->cmd);
// 				free(temp->args);
// 				free(temp);
// 			}
// 			return (NULL);
// 		}
//
// 		i = 0;
// 		arg_count = 0;
//
// 		// Check if the first token is a WORD
// 		if (token_list->type != WORD)
// 		{
// 			fprintf(stderr, "Error: First token is not a command (WORD)\n");
// 			free(cmd_data);
// 			return NULL;
// 		}
//
// 		// Assign the command
// 		token_val = ft_strdup(token_list->val);
// 		cmd_data->cmd = token_val;
// 		if (!cmd_data->cmd)
// 		{
// 			free(cmd_data);
// 			return (NULL);
// 		}
//
// 		// Initialize the redirection field in cmd_data
// 		cmd_data->redir = redir_list;
// 		cmd_data->next = NULL; // Initialize the next pointer
//
// 		// Set the current token pointer to the next token after the command
// 		cur = token_list->next;
//
// 		// First pass: Count arguments using a while loop
// 		while (cur != NULL && cur->type != PIPE)
// 		{
// 			if (get_token_type(cur->val) == WORD)
// 			{
// 				arg_count++; // Count valid arguments
// 			}
// 			cur = cur->next; // Move to the next token
// 		}
// 		// Allocate space for arguments
// 		cmd_data->args = safe_malloc((arg_count + 1) * sizeof(char*));
// 		if (!cmd_data->args)
// 		{
// 			free(cmd_data->cmd);
// 			free(cmd_data);
// 			return (NULL);
// 		}
//
// 		// Second pass: Fill args array using a while loop
// 		cur = token_list->next; // Reset cur to start from the first argument
// 		i = 0; // Reset index for args
// 		while (cur != NULL && cur->type != PIPE)
// 		{
// 			// Check if the token is a WORD
// 			if (get_token_type(cur->val) == WORD)
// 			{
// 				cmd_data->args[i] = ft_strdup(cur->val);
// 				if (!cmd_data->args[i])
// 				{
// 					// Handle allocation failure and free previously allocated args
// 					while (i > 0)
// 					{
// 						// Free previously allocated arguments
// 						free(cmd_data->args[--i]);
// 					}
// 					free(cmd_data->args);
// 					free(cmd_data->cmd);
// 					free(cmd_data);
// 					return (NULL);
// 				}
// 				i++;
// 			}
// 			cur = cur->next; // Move to the next token
// 		}
// 		cmd_data->args[i] = NULL; // Null-terminate the args array
// 		printf("builtincheck deactived \n");
// 		// cmd_data->builtin = check_for_builtin(cmd_data->cmd); // Check if it's a builtin command
//
// 		// Add the command to the command list
// 		if (head == NULL)
// 		{
// 			head = cmd_data; // Set head if list is empty
// 			tail = cmd_data; // Initialize tail
// 		}
// 		else
// 		{
// 			tail->next = cmd_data; // Link the new command
// 			tail = cmd_data; // Update tail
// 		}
//
// 		// Move to the next token (after the pipe if it exists)
// 		if (cur != NULL && cur->type == PIPE)
// 		{
// 			token_list = cur->next; // Skip the pipe and continue
// 		}
// 		else
// 		{
// 			break; // Exit if no more commands
// 		}
// 	}
//
// 	return (head); // Return the head of the command list
// }

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
	t_cmd* cmd_data = safe_malloc(sizeof(t_cmd));
	if (!cmd_data)
		return NULL;

	cmd_data->cmd = ft_strdup(token_val); // Duplicate the command string
	if (!cmd_data->cmd)
	{
		free(cmd_data);
		return NULL;
	}

	cmd_data->redir = redir_list;
	cmd_data->next = NULL;
	return cmd_data;
}

// Function to count the number of arguments in the token list (up to a pipe)
size_t count_arguments(t_token* token_list)
{
	size_t arg_count = 0;
	t_token* cur = token_list;

	while (cur != NULL && cur->type != PIPE)
	{
		if (get_token_type(cur->val) == WORD)
		{
			arg_count++;
		}
		cur = cur->next;
	}
	return arg_count;
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

	return head; // Return the head of the command list
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

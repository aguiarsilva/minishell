
#include "lib/minishell.h"

void	print_env_list(t_env *lst)
{
	t_env	*current;

	current = lst;
	while (current)
	{
		printf("Key: %s, Value: %s, EC: %d\n",
			   current->key ? current->key : "(null)",
			   current->value ? current->value : "(null)",
			   current->exit_code);
		current = current->next;
	}
}

void	print_token_lst(t_token* token)
{
	int	index; // Index to keep track of the position in the list

	index = 0;
	while (token != NULL)
	{
		printf("Token %d: \n", index);
		if (token->val)
			printf("  Value: %s\n", token->val);
		else
			printf("  Value: (null)\n");

		printf("  Type: %d\n", token->type); // Print the token type
		printf("  EOF Flag: %s\n", token->eof_flag ? "true" : "false");
		token = token->next; // Move to the next token
		index++; // Increment index
	}
}

void	print_env_node(t_env *node) // debug only
{
	t_env	*current;

	current = node;
	while (current)
	{
		printf("Key: ");
		if (current->key)
			printf("%s", current->key);
		else
			printf("(null)");
		printf(", Value: ");
		if (current->value)
			printf("%s", current->value);
		else
			printf("(null)");
		printf(", EC: %d\n", current->exit_code);
		current = current->next;
	}
}

void	print_redir_list(t_redir *redir_head) // will delete or put in seperate files
{
	t_redir	*current; // Start at the head of the list
	printf("\nin print_redir_list function \n");

	current = redir_head;
	// Check if the list is empty
	if (current == NULL)
	{
		printf("The redirection list is empty.\n");
		return;
	}

	printf("Redirection List:\n");
	while (current != NULL)
	{
		// Print file name and type
		printf("File Name: %s, Type: ", current->file_name);

		// Print the type as a string
		switch (current->type){
			case REDIR_IN:
				printf("REDIR_IN\n");
				break;
			case REDIR_OUT:
				printf("REDIR_OUT\n");
				break;
			case APPEND:
				printf("APPEND\n");
				break;
			case HEREDOC:
				printf("HEREDOC\n");
				break;
			case PIPE:
				printf("PIPE\n");
				break;
			case WORD:
				printf("WORD\n");
				break;
			default:
				printf("UNKNOWN\n");
				break;
		}
		current = current->next; // Move to the next node
	}
}

void	print_cmd(t_cmd* command)
{
	int	i;
	size_t	lst_size;
//	t_cmd	*current;

	lst_size = 0;
	// Check if the command list is empty
	if (command == NULL)
	{
		printf("Command list is empty.\n");
		return;
	}

	// Iterate through the list of commands
	while (command != NULL)
	{
		i = 0;
		// Print command (cmd)
		if (command->cmd != NULL)
			printf("\nCommand: %s\n", command->cmd);
		else
			printf("Command: (null)\n");
		// Print arguments (args)
		if (command->args != NULL)
		{
			printf("Arguments:\n");
			while (command->args[i] != NULL)
			{
				printf("  Arg[%d]: %s\n", i, command->args[i]);
				i++;
			}
		}
		else
			printf("Arguments: (null)\n");
		// Print built-in status
		printf("Built-in: %d\n", command->builtin);
		// Move to the next command in the list
		lst_size++;
		command = command->next;
	}
	printf("cmd_list contains %ld cmds\n", lst_size);
}

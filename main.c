
#include "lib/minishell.h"

// Function to concatenate argv into a single-dimensional char array
char* concat_argv(int argc, char* argv[])
{
	// Step 1: Calculate total length needed for concatenated string
	int total_length = 0;
	for (int i = 1; i < argc; i++)
	{
		total_length += strlen(argv[i]) + 1; // +1 for the space or null terminator
	}

	// Step 2: Allocate memory for the single-dimensional array
	char* one_dim_array = malloc(total_length * sizeof(char));
	if (one_dim_array == NULL)
	{
		return NULL; // Return NULL on allocation failure
	}

	// Step 3: Copy the arguments into the single-dimensional array
	strcpy(one_dim_array, argv[1]); // Copy the first argument
	for (int i = 2; i < argc; i++)
	{
		strcat(one_dim_array, " "); // Add space between arguments
		strcat(one_dim_array, argv[i]);
	}

	return one_dim_array; // Return the concatenated string
}

void print_token(t_token* token)
{
	int index = 0; // Index to keep track of the position in the list

	while (token != NULL)
	{
		printf("Token %d: \n", index);
		printf("  Value: %s\n", token->val ? token->val : "(null)");
		printf("  Type: %d\n", token->type); // Print the token type
		token = token->next; // Move to the next token
		index++; // Increment index
	}
}

void print_cmd(t_cmd* command)
{
	int i;

	// Check if the command list is empty
	if (command == NULL) {
		printf("Command list is empty.\n");
		return;
	}

	// Iterate through the list of commands
	while (command != NULL)
	{
		i = 0;

		// Print command (cmd)
		if (command->cmd != NULL)
		{
			printf("\nCommand: %s\n", command->cmd);
		} else
		{
			printf("Command: (null)\n");
		}

		// Print arguments (args)
		if (command->args != NULL)
		{
			printf("Arguments:\n");
			while (command->args[i] != NULL)
			{
				printf("  Arg[%d]: %s\n", i, command->args[i]);
				i++;
			}
		} else
		{
			printf("Arguments: (null)\n");
		}

		// Print built-in status
		printf("Built-in: %d\n", command->builtin);

		// Move to the next command in the list
		command = command->next;
	}
	printf("\n");
}

// will be moved out of main
int	main(const int argc, char *argv[], char *env[])
{
	t_cmd	*cmd_data;
	t_token	*token_list;
	t_redir	*redir_lst;
	char	*result;
//	char	**input;
//	int		i;

// // was working with this part
// 	input = safe_malloc(argc * sizeof(char *));
// 	if (!input)
// 		return (-1);

// 	i = 0;
// 	while (i < argc -1)
// 	{
// 		input[i] = ft_strdup(argv[i + 1]);
// 		printf("input[%d] = %s\n", i, input[i]);
// 		if (!input[i])
// 			return (-1);
// 		i++;
// 	}
//	int len = strlen(input[1]);
//	printf ("len = %d\n", len);
//	i = 0;
//	while (i < argc)
//	{
//		printf("input[%d] = %s\n", i, input[i]);
//		i++;
//	}
 	// char	*result = concat_argv(argc, argv);
	result = readline("");
	token_list = build_list(result);
	assign_token_type(token_list);
	print_token(token_list);
	redir_lst = extract_redirection_list_from_tokens(token_list);
	cmd_data = fill_cmd(token_list, redir_lst);
//	fprintf(stderr, "after fill cmd\n");
	print_cmd(cmd_data);
//	fprintf(stderr, "after print cmd\n");
	if (cmd_data == NULL)
		return (-1);
	run_process(cmd_data, env);
}




#include "lib/minishell.h"


// Function to concatenate argv into a single-dimensional char array
char *concat_argv(int argc, char *argv[]) {
    // Step 1: Calculate total length needed for concatenated string
    int total_length = 0;
    for (int i = 1; i < argc; i++) {
        total_length += strlen(argv[i]) + 1; // +1 for the space or null terminator
    }

    // Step 2: Allocate memory for the single-dimensional array
    char *one_dim_array = malloc(total_length * sizeof(char));
    if (one_dim_array == NULL) {
        return NULL; // Return NULL on allocation failure
    }

    // Step 3: Copy the arguments into the single-dimensional array
    strcpy(one_dim_array, argv[1]);  // Copy the first argument
    for (int i = 2; i < argc; i++) {
        strcat(one_dim_array, " ");   // Add space between arguments
        strcat(one_dim_array, argv[i]);
    }

    return one_dim_array; // Return the concatenated string
}

// void print_token(t_token *token) {
//     while (token != NULL) {
//         printf("Token value: %s\n", token->val ? token->val : "(null)");
//         printf("Token type: %d\n", token->type);  // Print the token type
//         printf("Next token: %s\n", token->next ? "Exists" : "NULL");
//         printf("-------------------------\n");
//         token = token->next;  // Move to the next token
//     }
// }

void print_token(t_token *token) {
    int index = 0;  // Index to keep track of the position in the list

    while (token != NULL) {
        printf("Token %d: \n", index);
        printf("  Value: %s\n", token->val ? token->val : "(null)");
        printf("  Type: %d\n", token->type);  // Print the token type
        token = token->next;  // Move to the next token
        index++;              // Increment index
    }
}

void print_cmd(t_cmd *command) {
    int i = 0;

    // Print command (cmd)
    if (command->cmd != NULL) {
        printf("Command: %s\n", command->cmd);
    } else {
        printf("Command: (null)\n");
    }

    // Print arguments (args)
    if (command->args != NULL) {
        printf("Arguments:\n");
        while (command->args[i] != NULL) {
            printf("  Arg[%d]: %s\n", i, command->args[i]);
            i++;
        }
    } else {
        printf("Arguments: (null)\n");
    }

    // Print built-in status
    printf("Built-in: %d\n", command->builtin);
}

// will be moved out of main
int	main(int argc, char *argv[], char *env[])
{
	pid_t	process_id;
	t_cmd	*cmd_data;
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
 	char *result = concat_argv(argc, argv);
	t_token *token_list = build_list(result);
	assign_token_type(token_list);
	print_token(token_list);
	cmd_data = fill_cmd(token_list);
	print_cmd(cmd_data);
	process_id = fork();
	if (process_id < 0)
	{
		free_cmd_data(cmd_data);
		print_error_msg_and_exit(ERR_FORK);
	}
	//in childprocess
	if (process_id == 0)
	{
		if (cmd_data->builtin)
		{
			run_builtin(cmd_data, env);
		}
		else
		{
			executor(cmd_data, env);
			print_error_msg_and_exit(ERR_UNKNOWN);
		}
	}
	else
	//in parentprocess
	{
		free(cmd_data);
		check_child_status(process_id);
	}

}



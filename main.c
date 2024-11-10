
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

	return (one_dim_array); // Return the concatenated string
}

// everything before will be moved out of main
int	main(const int argc, char *argv[], char *env[])
{
	t_cmd	*cmd_lst;
	t_token	*token_list;
	t_redir	*redir_lst;
	char	*result;
	t_env	*env_lst;


	if (argc <= 1)
		result = readline("");
	else
 		result = concat_argv(argc, argv); // just for faster debugging
	env_lst = create_env(env, argv);
	if (!env_lst)
		return (1);
//	print_env_list(env_lst);
	token_list = build_list(result, env_lst); // env_lst is not used in any function in build_list
	assign_token_type(token_list);
	print_token(token_list);
	redir_lst = extract_redirection_list_from_tokens(token_list);
	cmd_lst = fill_cmd(token_list, redir_lst);
	print_cmd(cmd_lst);
	if (cmd_lst == NULL)
		return (-1);
	run_process(cmd_lst, &env_lst);
	free(result);
}





#include "lib/minishell.h"

// Function to concatenate argv into a single-dimensional char array // only for faster debugging
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

char	*ft_get_prompt(t_env **env_lst)
{
	char	*result;

	result = readline("\033[1;36mminishell\033[34m$ \033[0m");
	if (!result)
		builtin_exit(NULL, env_lst);
	add_history(result);
	return (result);
}

void	run_minishell(t_env **env_lst, char *input)
{
	t_cmd	*cmd_lst;
	t_token	*token_list;
	t_redir	*redir_lst;

	token_list = build_lst(input, env_lst);
	if (check_if_token_list_right(token_list) == false)
	{
		free_tk(token_list);
		return ;
	}
	redir_lst = create_redir_lst_from_tokens(token_list);
	print_token_lst(token_list);
	cmd_lst = fill_cmd_lst(token_list, redir_lst);
//	print_cmd(cmd_lst);
	if (cmd_lst == NULL)
	{
		free_tk(token_list);
		return ;
	}
	free_tk(token_list);
	run_process(cmd_lst, env_lst);
	free_cmd_list(cmd_lst);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*input;
	t_env	*env_lst;
	void	(*past_signal[2])(int);

	env_lst = create_env_lst(env, argv);
	if (!env_lst)
		return (1);
	if (argc > 1)
		exit (1);
	while (1)
	{
		setup_signals();
		g_signal = 0;
		input = ft_get_prompt(&env_lst);
		run_minishell(&env_lst, input);
		reset_signals(past_signal);
		free(input);
	}
}

// int	main(const int argc, char *argv[], char *env[]) //added while true to test cmds interacting with each other
// {
// 	t_cmd	*cmd_lst;
// 	t_token	*token_list;
// 	t_redir	*redir_lst;
// 	char	*result;
// 	t_env	*env_lst;
// 	void	(*past_signal[2])(int);
//
// 	if (argc <= 1)
// 	{
// 		env_lst = create_env(env, argv);
// 		if (!env_lst)
// 			return (1);
// //		debug_env_list(env_lst, "After env creation");
// 		signal(SIGINT, interrupt_signal);
// 		signal(SIGQUIT, SIG_IGN);
// 		while (1)
// 		{
// 			g_signal = 0;
// 			result = readline("\033[1;36mminishell\033[34m$ \033[0m");
// 			if (result == NULL)
// 			{
// 				ft_printf("\nexit\n");
// 				break ;
// 			}
// 			add_history(result);
// 			token_list = build_lst(result, &env_lst);
// 			assign_token_type(token_list);
// 			print_token_lst(token_list);
// 			redir_lst = create_redir_lst_from_tokens(token_list);
// 			cmd_lst = fill_cmd_lst(token_list, redir_lst);
// 			print_cmd(cmd_lst);
// 			if (cmd_lst == NULL)
// 			{
// 				free_tk(token_list);
// 				free_cmd_list(cmd_lst);
// 				free(result);
// 				continue ;
// 			}
// 			signal_setter(past_signal);
// //			print_env_list(env_lst);
// 			run_process(cmd_lst, &env_lst);
// 			signal_restore(past_signal);
// 			free_cmd_list(cmd_lst);
// 			free_tk(token_list);
// 			free(result);
// 		}
// 	}
// 	else
// 	{
// 	result = concat_argv(argc, argv); // just for faster debugging
// 	env_lst = create_env(env, argv);
// 	// free_env_list(&env_lst);
// 	// print_env_list(env_lst);
// 	token_list = build_lst(result, &env_lst); // env_lst is not used in any function in build_list
// 	assign_token_type(token_list);
// 	print_token_lst(token_list);
// 	redir_lst = create_redir_lst_from_tokens(token_list);
// 	cmd_lst = fill_cmd_lst(token_list, redir_lst);
// 	print_cmd(cmd_lst);
// 	// free_tk(token_list);
// 	if (cmd_lst == NULL)
// 	{
// 		free_tk(token_list);
// 		free_cmd_list(cmd_lst);
// 		free(result);
// 		return (0);
// 	}
// 	// signal_setter(past_signal);
// 	run_process(cmd_lst, &env_lst);
// 	// signal_restore(past_signal);
// 	// print_env_list(env_lst);
// 	free_cmd_list(cmd_lst);
// 	free_tk(token_list);
// 	free(result);
// 	}
// }

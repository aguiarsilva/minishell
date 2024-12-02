/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:00:19 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/12/02 14:18:03 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/minishell.h"

char	*ft_get_prompt(t_env **env_lst)
{
	char	*result;

	result = readline(
			"\001\033[0;32m\002minishell\001\033[1;34m\002$ \001\033[0m\002");
	if (g_signal == 130)
	{
		update_exit_code(*env_lst, 130);
		g_signal = 0;
		return (NULL);
	}
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
		set_value_in_env_lst(*env_lst, "EC", "2");
		free_tk(token_list);
		return ;
	}
	redir_lst = create_redir_lst_from_tokens(token_list);
	cmd_lst = fill_cmd_lst(token_list, redir_lst);
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
	if (argc > 1 || !env_lst)
		return (1);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		set_signals(past_signal);
		g_signal = 0;
		input = ft_get_prompt(&env_lst);
		if (!input)
		{
			restore_signals(past_signal);
			break ;
		}
		run_minishell(&env_lst, input);
		free(input);
		restore_signals(past_signal);
	}
}

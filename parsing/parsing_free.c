/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 23:13:11 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/12/01 23:13:11 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	cleanup_args(char **args, int count)
{
	int	i;

	if (args == NULL)
		return ;
	i = 0;
	while (i < count)
	{
		if (args[i] != NULL)
		{
			free(args[i]);
			args[i] = NULL;
		}
		i++;
	}
	free(args);
}

void	free_redir_list(t_redir *redir_list)
{
	t_redir	*temp;

	if (redir_list == NULL)
		return ;
	while (redir_list)
	{
		temp = redir_list->next;
		if (redir_list->file_name != NULL && redir_list->file_name[0] != '\0')
		{
			free(redir_list->file_name);
			redir_list->file_name = NULL;
		}
		free(redir_list);
		redir_list = temp;
	}
}

void	free_command_contents(t_cmd *cmd)
{
	int	args_count;

	if (cmd->cmd)
	{
		free(cmd->cmd);
		cmd->cmd = NULL;
	}
	if (cmd->args)
	{
		args_count = count_arg_from_args(cmd->args);
		cleanup_args(cmd->args, args_count);
		cmd->args = NULL;
	}
}

void	free_cmd_list(t_cmd *cmd_list)
{
	int		i;
	t_cmd	*next_cmd;

	i = 1;
	while (cmd_list)
	{
		next_cmd = cmd_list->next;

		free_command_contents(cmd_list);
		if (i == 1)
			free_redir_list(cmd_list->redir);
		free(cmd_list);
		cmd_list = next_cmd;
		i++;
	}
}

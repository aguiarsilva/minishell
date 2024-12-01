

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
		if (redir_list->file_name != NULL)
		{
			free(redir_list->file_name);
			redir_list->file_name = NULL;
		}
		free(redir_list);
		redir_list = temp;
	}
}

void	free_cmd_node(t_cmd *cmd_node)
{
	int	i;

	i = 0;
	if (!cmd_node)
		return;
	if (cmd_node->cmd != NULL)
	{
		free(cmd_node->cmd);
		cmd_node->cmd = NULL;
	}
	if (cmd_node->args != NULL)
	{
		while (cmd_node->args[i] != NULL)
		{
			free(cmd_node->args[i]);
			cmd_node->args[i] = NULL;
			i++;
		}
		free(cmd_node->args);
		cmd_node->args = NULL;
	}
	free_redir_list(cmd_node->redir);
	free(cmd_node);
	cmd_node = NULL;
}

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*temp;

	while (cmd_list)
	{
		temp = cmd_list->next;
		free_cmd_node(cmd_list);
		cmd_list = temp;
	}
}

void	free_all(t_cmd *cmd_head, t_env **env_head)
{
	free_cmd_list(cmd_head);
	free_env_lst(env_head);
}

t_cmd	*cleanup_cmd_list(t_cmd *head)
{
	free_cmd_list(head);
	return (NULL);
}

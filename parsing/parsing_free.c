

#include "../lib/minishell.h"

void	cleanup_args(char **args, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void free_redir_list(t_redir *redir_list)
{
	t_redir	*temp;

	while (redir_list)
	{
		temp = redir_list->next;
		free(redir_list->file_name);
		free(redir_list);
		redir_list = temp;
	}
}

void free_cmd_node(t_cmd *cmd_node)
{
	if (!cmd_node)
		return;

	free(cmd_node->cmd);
	if (cmd_node->args)
	{
		for (int i = 0; cmd_node->args[i]; i++)
			free(cmd_node->args[i]);
		free(cmd_node->args);
	}
	free_redir_list(cmd_node->redir);
	free(cmd_node);
}


void free_cmd_list(t_cmd *cmd_list)
{
	t_cmd *temp;

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

t_cmd	*cleanup_cmd_list(t_cmd *head) // should combine them
{
	free_cmd_list(head);
	return (NULL);
}



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
	t_redir *temp;

	// printf("Freeing redirection list\n");

	if (redir_list == NULL)
	{
		// printf("Redir list is NULL, nothing to free\n");
		return;
	}

	while (redir_list)
	{
		temp = redir_list->next;

		// printf("Freeing redir node with filename: %s\n",
		// 	   redir_list->file_name ? redir_list->file_name : "NULL");

		if (redir_list->file_name != NULL)
		{
			free(redir_list->file_name);
			redir_list->file_name = NULL;
		}

		free(redir_list);
		redir_list = temp;
	}
}

// void	free_cmd_node(t_cmd *cmd_node)
// {
// 	int	i;
//
// 	i = 0;
// 	if (!cmd_node)
// 		return;
// 	if (cmd_node->cmd != NULL)
// 	{
// 		free(cmd_node->cmd);
// 		cmd_node->cmd = NULL;
// 	}
// 	if (cmd_node->args != NULL)
// 	{
// 		while (cmd_node->args[i] != NULL)
// 		{
// 			free(cmd_node->args[i]);
// 			cmd_node->args[i] = NULL;
// 			i++;
// 		}
// 		free(cmd_node->args);
// 		cmd_node->args = NULL;
// 	}
// 	free_redir_list(cmd_node->redir);
// 	free(cmd_node);
// 	cmd_node = NULL;
// }
//
// void	free_cmd_list(t_cmd *cmd_list)
// {
// 	t_cmd	*temp;
//
// 	while (cmd_list)
// 	{
// 		temp = cmd_list->next;
// 		free_cmd_node(cmd_list);
// 		cmd_list = temp;
// 	}
// }

void free_cmd_list(t_cmd *cmd_list)
{
	t_cmd  *temp;
	t_redir *processed_redir[100] = {NULL}; // Fixed-size array to track processed redir lists
	int processed_count = 0;
	int i;
	// printf("called free_cmd_list\n");
	while (cmd_list)
	{
		temp = cmd_list->next;

		// Check if this redir list has been processed
		int already_processed = 0;
		for (i = 0; i < processed_count; i++)
		{
			if (processed_redir[i] == cmd_list->redir)
			{
				already_processed = 1;
				break;
			}
		}

		// Free redir list if not already processed
		if (cmd_list->redir && !already_processed)
		{
			if (processed_count < 100) // Prevent buffer overflow
			{
				processed_redir[processed_count++] = cmd_list->redir;
			}
			free_redir_list(cmd_list->redir);
		}

		// Free command node contents
		if (cmd_list->cmd != NULL)
		{
			free(cmd_list->cmd);
			cmd_list->cmd = NULL;
		}

		if (cmd_list->args != NULL)
		{
			int arg_idx = 0;
			while (cmd_list->args[arg_idx] != NULL)
			{
				free(cmd_list->args[arg_idx]);
				cmd_list->args[arg_idx] = NULL;
				arg_idx++;
			}
			free(cmd_list->args);
			cmd_list->args = NULL;
		}

		free(cmd_list);
		cmd_list = temp;
	}
}

void	free_all(t_cmd *cmd_head, t_env **env_head)
{
	// printf("called free_all\n");
	free_cmd_list(cmd_head);
	free_env_lst(env_head);
}

t_cmd	*cleanup_cmd_list(t_cmd *head)
{
	// printf("called cleanupcmdlist\n");
	free_cmd_list(head);
	return (NULL);
}



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

void	free_redir_list(t_redir *redir)
{
	t_redir	*redir_temp;
	t_redir	*next_redir;

	while (redir != NULL)
	{
		redir_temp = redir;
		next_redir = redir->next;

		if (redir_temp->file_name != NULL)
		{
//			printf("Freeing file name: %p\n", redir_temp->file_name);
			free(redir_temp->file_name);
			redir_temp->file_name = NULL;
		}
		free(redir_temp);
		redir = next_redir;
	}
}

void	free_cmd_list(t_cmd *head)
{
	t_cmd	*temp;
	int		i;

	while (head != NULL)
	{
		temp = head;

		if (temp->args)
		{
			i = 0;
			while (temp->args[i] != NULL)
				i++;
			cleanup_args(temp->args, i);
		}
		free(temp->cmd);
		head = head->next;
		free(temp);
	}
	// After freeing all commands, free the redirections causes segfault
//	free_redir_list(head->redir);
}




void	free_all(t_cmd *cmd_head, t_env **env_head)
{
	free_cmd_list(cmd_head);
	free_env_lst(env_head);
}

//void	free_cmd_list(t_cmd *head) old
//{
//	t_cmd	*temp;
//	int		i;
//
//	while (head != NULL)
//	{
//		temp = head;
//		if (temp->args)
//		{
//			i = 0;
//			while (temp->args[i] != NULL)
//				i++;
//			cleanup_args(temp->args, i);
//		}
//		free(temp->cmd);
//		head = head->next;
//		free(temp);
//	}
//}

t_cmd	*cleanup_cmd_list(t_cmd *head) // should combine them
{
	free_cmd_list(head);
	return (NULL);
}

void	free_tk(t_token *tk_list)
{
	t_token	*tk_list_placeholder;

	if (!tk_list)
		return ;
	while (tk_list)
	{
		free(tk_list->val);
		tk_list_placeholder = tk_list;
		tk_list = tk_list->next;
		free(tk_list_placeholder);
	}
}


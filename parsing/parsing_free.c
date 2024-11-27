

#include "../lib/minishell.h"

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
}

t_cmd	*cleanup_cmd_list(t_cmd *head) // should combine them
{
	free_cmd_list(head);
	return (NULL);
}

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


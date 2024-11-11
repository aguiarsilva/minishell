

#include "../lib/minishell.h"

void	free_cmd_list(t_cmd *head)
{
	t_cmd	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->cmd);
		free(temp->args);
		free(temp);
	}
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

t_cmd	*cleanup_cmd_list(t_cmd *head)
{
	free_cmd_list(head);
	return (NULL);
}
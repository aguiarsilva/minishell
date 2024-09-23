#include "../lib/minishell.h"

t_token *build_list(t_prompt *prompt, char *msg)
{
	t_token *head;
	t_token	*new;
	t_token	*curr;
	char	*store_prompt_msg;
	char	*token;

	store_prompt_msg = ft_strdup(msg);
	token = ft_strtok(save_prompt_msg, "|");
	nodes_init(&head, &curr, &new);
	while (token != NULL)
	{
		new = make_token(token);
		if (new == NULL)
		{
			free_list_of_token(new);
			return (NULL);
		}
		append_node(&head, &curr, new);
		multi_cmd_init(new, prompt);
		make_redir_list(new, prompt, token);
		token = ft_strtok(NULL, "|");
	}
	free(store_prompt_msg);
	return (head);
}

void	append_node(t_token **head, t_token **curr, t_token *new)
{
	if (*head == NULL)
	{
		*head = new;
		*curr = new;
	}
	else
	{
		(*curr)->next = new;
		*curr = new;
	}
}

void	nodes_init(t_token **head, t_token **cur, t_token **new)
{
	*head = NULL;
	*cur = NULL;
	*new = NULL;
}

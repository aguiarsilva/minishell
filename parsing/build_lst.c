

#include "../lib/minishell.h"

t_token	*build_lst(char *input, t_env **env_lst)
{
	t_token	*word_list;

	word_list = create_word_list(input, env_lst);
	assign_token_type(word_list);
	return (word_list);
}

void	add_new_token_to_lst(t_token **head, t_token **tail, t_token *new_token)
{
	if (*head == NULL)
	{
		*head = new_token;
		*tail = new_token;
	}
	else
	{
		(*tail)->next = new_token;
		*tail = new_token;
	}
}



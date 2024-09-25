#include "../lib/minishell.h"

t_redir *make_redir_node(char *file_name, t_type type)
{
	t_redir	*new_node;

	new_node = malloc(sizeof(t_redir));
	if (new_node == NULL)
		return (NULL);
	new_node->file_name = ft_strdup(file_name);
	if (new_node->file_name == NULL)
	{
		free(new_node);
		return (NULL);
	}
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

void	run_redir(t_redir **head, t_redir **cur, char *wd, t_type type)
{
	t_redir	*new_redir;

	new_redir = make_redir_node(wd, type);
	append_redir_node(head, cur, new_redir);
}

t_redir	*make_redir_list(t_token *new, t_prompt *prompt, char *msg)
{
	//build a list for the redirection tokens
	// check if redirection operator is in word
	// flag if it found as true
}
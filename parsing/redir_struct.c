

#include "../lib/minishell.h"

static t_redir	*init_redirection_node(t_token *token_node, int filetype)
{
	t_redir	*new_redir;
	char	*filename;

	new_redir = malloc(sizeof(t_redir));
	if (new_redir == NULL)
	{
		printf("Memory allocation failed for redirection node\n");
		return (NULL);
	}
	filename = token_node->val;
//	fprintf(stderr, "token_val: %s and file type: %d\n", filename, filetype); // debug print
	new_redir->file_name = ft_strdup(filename);
	if (new_redir->file_name == NULL)
	{
		free(new_redir);
		printf("Memory allocation failed for file_name\n");
		return (NULL);
	}
	new_redir->type = determine_redirection_type(filetype);
	// printf("DEBUG filename: %s and type after initialization: %d\n", new_redir->file_name, new_redir->type); //debug printf
	new_redir->next = NULL;
	return (new_redir);
}

// Main function to create the redirection struct and add it to the list
static t_redir	*create_redir_struct(t_redir **redir_head,
								t_token *token_node, int filetype)
{
	t_redir	*new_redir;
	t_redir	*last_redir;

	new_redir = init_redirection_node(token_node, filetype);
	if (new_redir == NULL)
		return (NULL);
	if (*redir_head == NULL)
		*redir_head = new_redir;
	else
	{
		last_redir = get_last_redirection_node(*redir_head);
		last_redir->next = new_redir;
	}
	return (*redir_head);
}

void	add_to_redir_lst(t_token *cur_token, t_redir **redir_lst,
						int file_type, t_token *prev_token)
{
	if (is_filename(cur_token->val) || cur_token->eof_flag
		||is_file_without_extension(prev_token, cur_token))
	{
		if (cur_token->eof_flag)
			create_redir_struct(redir_lst, prev_token, file_type);
		else
			create_redir_struct(redir_lst, cur_token, file_type);
	}
}

void	append_redir_node(t_redir **redir_lst, t_redir **last_redir,
						t_redir *new_redir)
{
	if (new_redir)
	{
		if (*redir_lst == NULL)
		{
			*redir_lst = new_redir;
			*last_redir = *redir_lst;
		}
		else
		{
			(*last_redir)->next = new_redir;
			*last_redir = new_redir;
		}
	}
}

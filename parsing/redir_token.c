

#include "../lib/minishell.h"
// Helper function to find the last redirection node in the list
static t_redir	*get_last_redirection_node(t_redir *redir_head)
{
	t_redir	*last_redir_node;

	last_redir_node = redir_head;
	while (last_redir_node && last_redir_node->next != NULL)
		last_redir_node = last_redir_node->next;
	return (last_redir_node);
}

// Helper function to create and initialize a new redirection node
static t_redir	*initialize_redirection_node(t_token *token_node, int filetype)
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
	printf("filename: %s and type after initialization: %d\n", new_redir->file_name, new_redir->type); //debug printf
	new_redir->next = NULL;
	return (new_redir);
}

// Main function to create the redirection struct and add it to the list
t_redir	*create_redir_struct(t_redir **redir_head,
								t_token *token_node, int filetype)
{
	t_redir	*new_redir;
	t_redir	*last_redir;

	new_redir = initialize_redirection_node(token_node, filetype);
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

void	add_to_redirection_list(t_token *cur_token, t_redir **redir_lst,
								int file_type, t_token *prev_token)
{
	if (is_filename(cur_token->val) || cur_token->eof_flag)
	{
		if (cur_token->eof_flag)
			create_redir_struct(redir_lst, prev_token, file_type);
		else
			create_redir_struct(redir_lst, cur_token, file_type);
	}
}

t_redir	*extract_redirection_list_from_tokens(t_token *token_lst)
{
	t_token	*cur_token;
	t_redir	*redir_lst;
	int		file_type;
	t_token	*prev_token;

	cur_token = token_lst;
	if (cur_token == NULL || get_token_type(cur_token->val) != WORD)
		return (NULL);
	redir_lst = NULL;
	prev_token = NULL;
	while (cur_token != NULL)
	{
		if (get_token_type(cur_token->val) == REDIR_IN)
			file_type = INPUT;
		if (get_token_type(cur_token->val) == HEREDOC)
			file_type = HEREDOC_INPUT;
		else if (get_token_type(cur_token->val) == APPEND)
			file_type = APPEND_OUTPUT;
		else if (get_token_type(cur_token->val) == REDIR_OUT)
			file_type = OUTPUT;
		handle_heredoc(cur_token, &cur_token, &prev_token, file_type);
		add_to_redirection_list(cur_token, &redir_lst, file_type, prev_token);
		prev_token = cur_token;
		cur_token = cur_token->next;
	}
	if (redir_lst == NULL)
		printf("redir_lst is NULL after creation\n"); // just debug will delete later
	print_redir_list(redir_lst);
	return (redir_lst);
}

// int flag_heredoc(t_token** tk_lst, t_cmd* new_cmd)
// {
// 	t_redir* file_name;
//
// 	if (!(*tk_lst)->next)
// 	{
// 		ft_putsrt_fd("Error: Must provide delimiter for heredoc!\n", 2);
// 		return (g_signal = 258, 1);
// 	}
// 	*tk_lst = (*tk_lst)->next;
// 	if ((*tk_lst)->type != WORD)
// 	{
// 		ft_putsrt_fd("Error: Must provide delimiter for heredoc!\n", 2);
// 		return (g_signal = 258, 1);
// 	}
// 	file_name = create_file((*tk_lst)->val, HEREDOC, NULL);
// 	if (!file_name)
// 		return (1);
// 	add_file_to_list(&new_cmd->redir, file_name);
// 	return (0);
// }
//
//

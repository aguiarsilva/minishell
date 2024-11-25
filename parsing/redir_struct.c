

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
	printf("DEBUG filename: %s and type after initialization: %d\n", new_redir->file_name, new_redir->type); //debug printf
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

//t_redir	*create_redir_lst_from_tokens(t_token *token_lst)
//{
//	t_token	*cur_token;
//	t_token	*prev_token;
//	t_redir	*redir_lst;
//	t_redir	*temp_redir;
//
//	cur_token = token_lst;
//	prev_token = NULL;
//	redir_lst = NULL;
//	if (cur_token == NULL || get_token_type(cur_token->val) != WORD)
//		return (NULL);
//	while (cur_token != NULL)
//	{
//		if (get_token_type(cur_token->val) == HEREDOC)
//		{
//			if (handle_heredoc_special_case(&cur_token, &prev_token))
//				continue ;
//		}
//		temp_redir = process_redirection_token(cur_token, &prev_token);
//		add_redir_to_head(temp_redir, &redir_lst);
//		prev_token = cur_token;
//		cur_token = cur_token->next;
//	}
//	return (redir_lst);
//}

//t_redir	*extract_redirection_list_from_tokens(t_token *token_lst) // working
//{
//	t_token	*cur_token;
//	t_redir	*redir_lst;
//	int		file_type;
//	t_token	*prev_token;
//
//	cur_token = token_lst;
//	if (cur_token == NULL || get_token_type(cur_token->val) != WORD)
//		return (NULL);
//	redir_lst = NULL;
//	prev_token = NULL;
//	while (cur_token != NULL)
//	{
//		file_type = -1;
//		if (get_token_type(cur_token->val) == REDIR_IN)
//			file_type = INPUT;
//		else if (get_token_type(cur_token->val) == HEREDOC)
//		{
//			if (cur_token->next && get_token_type(cur_token->next->val) == HEREDOC)
//			{
//				cur_token = cur_token->next;
//				prev_token = cur_token;
//				cur_token = cur_token->next;
//				continue ;
//			}
//			printf("set filetype heredoc\n");
//			file_type = HEREDOC_INPUT;
//		}
//		else if (get_token_type(cur_token->val) == APPEND)
//			file_type = APPEND_OUTPUT;
//		else if (get_token_type(cur_token->val) == REDIR_OUT)
//			file_type = OUTPUT;
//		if (file_type != -1)
//		{
//			if (file_type == HEREDOC_INPUT)
//			{
//				handle_heredoc(cur_token, &cur_token, &prev_token, file_type);
//				// After handle_heredoc, cur_token should be pointing to the temp file
//				if (cur_token != NULL)
//					add_to_redirection_list(cur_token, &redir_lst, file_type, prev_token);
//			}
//			else if (cur_token->next && get_token_type(cur_token->next->val) == WORD)
//			{
//				add_to_redirection_list(cur_token->next, &redir_lst, file_type, cur_token);
//			}
//		}
//		prev_token = cur_token;
//		cur_token = cur_token->next;
//	}
////	print_redir_list(redir_lst);
//	return (redir_lst);
//}



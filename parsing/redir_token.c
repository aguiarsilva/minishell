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
	// fprintf(stderr, "token_val: %s\n", filename);
	new_redir->file_name = ft_strdup(filename);
	if (new_redir->file_name == NULL)
	{
		free(new_redir);
		printf("Memory allocation failed for file_name\n");
		return (NULL);
	}
	// new_redir->type = token_node->type; // wrong node to define type because its always word
	if (filetype == INPUT)
		new_redir->type = REDIR_IN;
	else if (filetype == OUTPUT)
		new_redir->type = REDIR_OUT;
	else
		new_redir->type = WORD;
	printf("filename: %s and type after initialization: %d\n", new_redir->file_name, new_redir->type);
	new_redir->next = NULL;

	return (new_redir);
}

// Main function to create the redirection struct and add it to the list
t_redir	*create_redir_struct(t_redir **redir_head, t_token *token_node, int filetype)
{
	t_redir	*new_redir;

	new_redir = initialize_redirection_node(token_node, filetype);
	if (new_redir == NULL)
		return (NULL);
	if (*redir_head == NULL)
	{
		*redir_head = new_redir;
		// printf("Set new redir node as the head of the list.\n");
	}
	else
	{
		t_redir *last_redir = get_last_redirection_node(*redir_head);
		last_redir->next = new_redir;
		// printf("Appended new redir node to the end of the list.\n");
	}
	return (*redir_head); // Return the head of the list
}

bool	is_filename(const char *str)
{
	const char	*dot_position;
	const char	*file_extension;

	dot_position = ft_strrchr(str, '.');

	if (dot_position && dot_position != str && *(dot_position + 1) != '\0')
	{
		file_extension = dot_position + 1;
		while (*file_extension != '\0')
		{
			if (!ft_isalnum(*file_extension))
				return (false);
			file_extension++;
		}
		//		fprintf(stderr, "print recogniced file names %s\n", str);
		return (true);
	}
	return (false);
}

void	rm_newline(char **str)
{
	size_t	i;

	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	(*str)[i] = '\0';
}

int	create_heredoc(t_token *token_list)
{
	int		fd_temp;
	char	*buf[2];
	char	*filename;
	t_token	*delimit_node;

	if (token_list->next != NULL)
	{
		delimit_node = token_list->next;
//		fprintf(stderr, "next_node_val: %s\n", delimit_node->val);
	} else {
		fprintf(stderr, "next node is NULL\n");
	}
	filename = "temp0";
	fd_temp = open(filename, O_RDWR | O_CREAT | O_TRUNC, 00644);
	if (fd_temp == -1)
		return (1);
	while (1)
	{
		write(0, "> ", 2);
		buf[0] = get_next_line(STDIN_FILENO);
		fprintf(stderr, "buf0 %s\n", buf[0]);
		if (!buf[0])
			return (1);
		rm_newline(&buf[0]);
		if (ft_memcmp(delimit_node->val, buf[0], ft_strlen(delimit_node->val) + 1) == 0)
			break ;
//		buf[1] = check_expand(buf[0], -1, lst, 0);
//		if (!buf[1])
//			return (1);
		ft_putstr_fd_mod(buf[0], fd_temp);
		free(buf[0]);
//		ft_putstr_fd_mod(buf[1], fd_temp);
//		free(buf[1]);
	}
	free(buf[0]);
	return (close(fd_temp), 0);
}
t_redir	*extract_redirection_list_from_tokens(t_token *token_list)
{
	t_token	*cur_token;
	t_redir	*redir_list;
	int		filetype;
	t_token	*file_token;
	t_token	*prev_token = NULL;
	cur_token = token_list;
	if (cur_token == NULL)
		return (NULL);
	redir_list = NULL;
	filetype = NOFILE;
	if (get_token_type(cur_token->val) != WORD) // prevent create redir struct when not needed but maybe edgecases
		return (NULL);
	while (cur_token != NULL)
	{
		prev_token = cur_token;
		if (get_token_type(cur_token->val) == REDIR_IN)
			filetype = INPUT;
		else if (get_token_type(cur_token->val) == REDIR_OUT)
			filetype = OUTPUT;
		else if (get_token_type(cur_token->val) == HEREDOC)
		{
			filetype = INPUT;
			create_heredoc(cur_token);
			// create token add it between the current_node and next node
			file_token = make_token("temp0", WORD);
			// Insert the file_token between current token and next token
			if (cur_token->next != NULL)
			{
				file_token->next = cur_token->next; // Set file_token's next to cur_token's next
				cur_token->next = file_token;       // Link cur_token to file_token
			}
			else
			{
				cur_token->next = file_token; // If no next token, just append
				file_token->next = NULL;      // The new token is now the last node
			}
			// After insertion, skip the newly inserted token (skip to the next token after file_token)
			cur_token = file_token->next;
			continue; // Skip the current iteration since we've already handled the new token
		}
		if (is_filename(cur_token->val) || cur_token->eof_flag == true)
		{
			if (cur_token->eof_flag == true)
			{
				printf("prev node is : %s\n", prev_token->val);
				redir_list = create_redir_struct(&redir_list, prev_token, filetype); // still not the right node
				if (redir_list == NULL)
				{
					printf("Failed to create redirection struct for: %s\n", cur_token->val);
					return (NULL);
				}
			}
			else
			{
				printf("else called?\n");
				redir_list = create_redir_struct(&redir_list, cur_token, filetype);
				if (redir_list == NULL)
				{
					printf("Failed to create redirection struct for: %s\n", cur_token->val);
					return (NULL);
				}
			}

		}
		cur_token = cur_token->next;
	}
	if (redir_list == NULL)
		printf("redir_list is NULL after creation\n"); // just debug will delete later

	print_redir_list(redir_list);
	return (redir_list);
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

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
	fprintf(stderr, "token_val: %s and file type: %d\n", filename, filetype);
	new_redir->file_name = ft_strdup(filename);
	if (new_redir->file_name == NULL)
	{
		free(new_redir);
		printf("Memory allocation failed for file_name\n");
		return (NULL);
	}
	// new_redir->type = token_node->type; // wrong node to define type because its always word
	if (filetype == INPUT || filetype == HEREDOC_INPUT)
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
//		fprintf(stderr, "buf0 %s\n", buf[0]);
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

void	insert_token_between(t_token *cur_token, t_token *new_token)
{
	if (cur_token->next != NULL)
	{
		new_token->next = cur_token->next;
		cur_token->next = new_token;
	}
	else
	{
		cur_token->next = new_token;
		new_token->next = NULL;
	}
}

void	handle_heredoc(t_token *cur_token, t_token **next_token,
					t_token **prev_token, int file_type)
{
	t_token	*file_token;

	file_token = NULL;
	if (file_type == HEREDOC_INPUT)
	{
		create_heredoc(cur_token);
		file_token = make_token("temp0", WORD);
		insert_token_between(cur_token, file_token);
		*next_token = file_token->next;
		*prev_token = file_token;
	}
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
		else if (get_token_type(cur_token->val) == REDIR_OUT)
			file_type = OUTPUT;
		handle_heredoc(cur_token, &cur_token, &prev_token, file_type);
		add_to_redirection_list(cur_token, &redir_lst, file_type, prev_token);
		prev_token = cur_token;
		cur_token = cur_token->next;
	}
		if (redir_lst == NULL)
			printf("redir_lst is NULL after creation\n"); // just debug will delete later
//	print_redir_list(redir_lst);
	return (redir_lst);
}

//t_redir	*extract_redirection_list_from_tokens(t_token *token_lst) not refactoed
//{
//	t_token	*cur_token;
//	t_redir	*redir_lst;
//	int		file_type;
//	t_token	*file_token;
//	t_token	*prev_token;
//
//	cur_token = token_lst;
//	if (cur_token == NULL)
//		return (NULL);
//	redir_lst = NULL;
//	file_type = NOFILE;
//	prev_token = NULL;
//	if (get_token_type(cur_token->val) != WORD)
//		return (NULL);
//	while (cur_token != NULL)
//	{
//		file_type = get_file_type(cur_token);
//		if (file_type == HEREDOC_INPUT)
//		{
//			create_heredoc(cur_token);
//			file_token = make_token("temp0", WORD);
//			insert_token_between(cur_token, file_token);
//			prev_token = file_token;
//			cur_token = file_token->next;
//			continue ;
//		}
//		if (is_filename(cur_token->val) || cur_token->eof_flag == true)
//		{
//			if (cur_token->eof_flag)
//				create_redir_struct(&redir_lst, prev_token, file_type);
//			else
//				create_redir_struct(&redir_lst, cur_token, file_type);
//		}
//		prev_token = cur_token;
//		cur_token = cur_token->next;
//	}
//	if (redir_lst == NULL)
//		printf("redir_list is NULL after creation\n"); // just debug will delete later
////  print_redir_list(redir_list);
//	return (redir_lst);
//}

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

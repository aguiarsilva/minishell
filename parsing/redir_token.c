#include "../lib/minishell.h"

// Helper function to find the last redirection node in the list
static t_redir	*get_last_redirection_node(t_redir *redir_head)
{
	t_redir	*current_redir; // maybe rename it later

	current_redir = redir_head;
	while (current_redir && current_redir->next != NULL)
		current_redir = current_redir->next;
	return (current_redir);
}

// Helper function to create and initialize a new redirection node
static t_redir	*initialize_redirection_node(t_token *token_node, int filetype)
{
	t_redir	*new_redir;
	char	*filename;

	new_redir= safe_malloc(sizeof(t_redir));
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
	// printf("Initialized redir struct for filename with type : %s %d \n", token_node->val, token_node->type);
	return (new_redir);
}

// Main function to create the redirection struct and add it to the list
t_redir *create_redir_struct(t_redir **redir_head, t_token *token_node, int filetype)
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

bool is_filename(const char *str)
{
	const char	*dot;
	const char	*file_extension;

	dot = ft_strrchr(str, '.');  // Find the last dot in the string

	if (dot && dot != str && *(dot + 1) != '\0')
	{
		file_extension = dot + 1;
		// Optional: Ensure the file extension only contains valid characters (e.g., alphanumeric)
		while (*file_extension != '\0')
		{
			if (!ft_isalpha(*file_extension))
				return (false);
			file_extension++;
		}
		//		fprintf(stderr, "print recogniced file names %s\n", str);
		return (true);
	}
	return (false);
}

void print_redir_list(t_redir *redir_head) // will delete or put in seperate files
{
	t_redir *current = redir_head; // Start at the head of the list
	printf("\nin print_redir_list function \n");

	// Check if the list is empty
	if (current == NULL)
	{
		printf("The redirection list is empty.\n");
		return;
	}

	printf("Redirection List:\n");
	while (current != NULL)
	{
		// Print file name and type
		printf("File Name: %s, Type: ", current->file_name);

		// Print the type as a string
		switch (current->type){
		case REDIR_IN:
			printf("REDIR_IN\n");
			break;
		case REDIR_OUT:
			printf("REDIR_OUT\n");
			break;
		case APPEND:
			printf("APPEND\n");
			break;
		case HEREDOC:
			printf("HEREDOC\n");
			break;
		case PIPE:
			printf("PIPE\n");
			break;
		case WORD:
			printf("WORD\n");
			break;
		default:
			printf("UNKNOWN\n");
			break;
		}
		current = current->next; // Move to the next node
	}
}

t_redir	*extract_redirection_list_from_tokens(t_token *token_list)
{
	t_token *current_token;
	t_redir	*redir_list;
	int		filetype;

	current_token = token_list;
	if (current_token == NULL)
		return (NULL);
	redir_list = NULL;
	filetype = NOFILE;
	if (get_token_type(current_token->val) != WORD) // prevent create redir struct when not needed but maybe edgecases
		return (NULL);
	while (current_token != NULL)
	{
		if (get_token_type(current_token->val) == REDIR_IN)
			filetype = INPUT;
		else if (get_token_type(current_token->val) == REDIR_OUT)
			filetype = OUTPUT;
		if (is_filename(current_token->val))
		{
			// redir_list = create_redir_struct(&redir_list, current_token->val);
			printf("filetype before create_redir_struct %d\n", filetype);
			redir_list = create_redir_struct(&redir_list, current_token, filetype);
			if (redir_list == NULL)
			{
				printf("Failed to create redirection struct for: %s\n", current_token->val);
				return (NULL);
			}
		}
		current_token = current_token->next;
	}
	if (redir_list == NULL)
	{
		printf("redir_list is NULL after creation\n");
	}
	// else
	// {
	// 	fprintf(stderr, "redir_list has been created\n");
	// }
	print_redir_list(redir_list);
	// fprintf(stderr, "printed redir_list_done\n");
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

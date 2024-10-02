#include "../lib/minishell.h"

t_token	*make_token(char *wd, t_type type)
{
	t_token	*new_tk;
	int		len;

	len = ft_strlen(wd);
	new_tk = malloc(sizeof(t_token));
	if (new_tk == NULL)
		return (NULL);
	new_tk->val = (char *)malloc(sizeof(char) * (len + 1));
	if (new_tk->val == NULL)
	{
		free(new_tk);
		return (NULL);
	}
	ft_strcpy(new_tk->val, wd);
	new_tk->next = NULL;
	new_tk->type = type;
	//new_tk->count_cmd = 0;
	//new_tk->count_wd = 0;
	//new_tk->multi_cmd = NULL;
	//new_tk->redir = NULL;
	return (new_tk);
}

/*t_token	*multi_cmd_init(t_token *new, t_prompt *prompt)
{
	char	*cp_val;
	char	*wd;
	bool	redir;

	redir = false;
	cp_val = ft_strdup(new->val);
	if (!cp_val)
		return (NULL);
	if (!multi_cmd_arr_init(new, cp_val))
		return (NULL);
	wd = ft_strtok_rm_quotes(cp_val, prompt->whitespace);
	while (wd != NULL)
	{
		if (is_redir_operator(wd))
			redir = true;
		else if (redir)
			redir = false;
		else
			new->multi_cmd[new->count_cmd++] = ft_strudp(wd);
		wd = ft_strtok_rm_quotes(NULL, prompt->whitespace);
	}
	new->multi_cmd[new->count_cmd] = NULL;
	free(cp_val);
	return (new);
}*/

/*bool	multi_cmd_arr_init(t_token *new, char *cp_val)
{
	new->count_wd = ft_count_words(new->val); //different count words.
	new->multi_cmd = malloc(sizeof(char *) * (new->count_wd + 1));
	if (!new->multi_cmd)
	{
		free(cp_val);
		return (false);
	}
	return (true);
}*/
t_type	get_token_type(char *token)
{
    if (ft_strcmp(token, "<") == 0)
        return REDIR_IN;
    else if (ft_strcmp(token, ">") == 0)
        return REDIR_OUT;
    else if (ft_strcmp(token, ">>") == 0)
        return APPEND;
    else if (ft_strcmp(token, "<<") == 0)
        return HEREDOC;
    else if (ft_strcmp(token, "|") == 0)
        return PIPE;
    else
        return WORD;  // Default type is WORD for commands/arguments
}

void	assign_token_type(t_token *token_list)
{
	t_token *current = token_list;
	while (current != NULL)
	{
		current->type = get_token_type(current->val);  // Assign type based on the value
		current = current->next;  // Move to the next token in the list
	}
}

void print_redir_list(t_redir *redir_head)
{
	t_redir *current = redir_head; // Start at the head of the list
	fprintf(stderr, "in print_redir_list function \n");

	// Check if the list is empty
	if (current == NULL)
		{
		fprintf(stderr, "The redirection list is empty.\n");
		return;
	}

	fprintf(stderr, "Redirection List:\n");
	while (current != NULL) {
		// Print the file_name and type of the current node
		fprintf(stderr,"File Name: %s\n", current->file_name);
		current = current->next; // Move to the next node
	}
}

// t_redir	*create_redir_struct(t_redir **redir_head, char *filename)
// {
// 	t_redir *new_redir_node;
// 	t_redir *current_redir;
//
// 	new_redir_node = safe_malloc(sizeof(t_redir));
// 	if (!new_redir_node)
// 		return (NULL);
// 	ft_bzero(new_redir_node, sizeof(*new_redir_node));
// 	new_redir_node->file_name = ft_strdup(filename);
// 	if (!new_redir_node->file_name)
// 	{
// 		free(new_redir_node);
// 		return (NULL);
// 	}
// 	//new_redir_node->type = SOME_DEFAULT_TYPE; // maybe detect if it is a input or output file
// 	new_redir_node->next = NULL;
//
// 	if (*redir_head == NULL)
// 		*redir_head = new_redir_node;
// 	else
// 	{
// 		current_redir = *redir_head;
// 		while (current_redir->next != NULL)
// 		{
// 			current_redir = current_redir->next;
// 		}
// 		current_redir->next = new_redir_node;
// 	}
// 	return (*redir_head);
// }

t_redir *create_redir_struct(t_redir **redir_head, char *filename) // with debug prints
{
	t_redir *new_redir_node;
	t_redir *current_redir;

	new_redir_node = safe_malloc(sizeof(t_redir));
	// new_redir_node = (t_redir *) malloc(sizeof(t_redir));
	if (!new_redir_node)
	{
		fprintf(stderr, "Memory allocation failed for new redirection node\n");
		return NULL; // Return NULL if allocation fails
	}

	// Initialize the new node
	new_redir_node->file_name = ft_strdup(filename);
	if (!new_redir_node->file_name)
	{
		free(new_redir_node);
		fprintf(stderr, "Memory allocation failed for file_name\n");
		return NULL; // Return NULL if allocation fails
	}
	new_redir_node->next = NULL; // Set the next pointer to NULL

	fprintf(stderr, "Creating redir struct for filename: %s\n", filename); // Debugging print

	// If the list is empty, set the new node as head
	if (*redir_head == NULL)
	{
		*redir_head = new_redir_node;
//		fprintf(stderr,"Set new node as head of the list.\n");
	} else
	{
		// Traverse to the end of the list and append
		current_redir = *redir_head;
		while (current_redir->next != NULL) {
			current_redir = current_redir->next;
		}
		current_redir->next = new_redir_node; // Append to the end
		fprintf(stderr,"Appended new node to the end of the list.\n");
	}

	return *redir_head; // Return the head of the list
}


bool is_filename(const char *str)
{
	const char *dot;
	const char *file_extension;

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

t_redir	*extract_redirection_list_from_tokens(t_token *token_list)
{
	t_token *current_token;
	t_redir	*redir_list;

	current_token = token_list;
	redir_list = NULL;

	while (current_token != NULL)
	{
		if (is_filename(current_token->val))
		{
			redir_list = create_redir_struct(&redir_list, current_token->val);
			if (redir_list == NULL)
			{
				fprintf(stderr, "Failed to create redirection struct for: %s\n", current_token->val);
				return (NULL);
			}
		}
		current_token = current_token->next;
	}
	if (redir_list == NULL)
	{
		fprintf(stderr, "redir_list is NULL after creation\n");
	}
	else
	{
		fprintf(stderr, "redir_list has been created\n");
	}
	// print_redir_list(redir_list);
	// fprintf(stderr, "printed redir_list_done\n");
	return (redir_list);
}

/*const char *get_type_name(t_type type) 
{
    switch (type) {
        case REDIR_IN: return "REDIR_IN";
        case REDIR_OUT: return "REDIR_OUT";
        case APPEND: return "APPEND";
        case HEREDOC: return "HEREDOC";
        case WORD: return "WORD";
        case PIPE: return "PIPE";
        default: return "UNKNOWN";
    }
}*/
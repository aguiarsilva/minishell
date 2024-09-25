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
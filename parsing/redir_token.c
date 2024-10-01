#include "../lib/minishell.h"

int	flag_heredoc(t_token **tk_lst, t_cmd *new_cmd)
{
	t_redir	*file_name;

	if (!(*tk_lst)->next)
	{
		ft_putsrt_fd("Error: Must provide delimiter for heredoc!\n", 2);
		return (g_signal = 258, 1);
	}
	*tk_lst = (*tk_lst)->next;
	if ((*tk_lst)->type != WORD)
	{
		ft_putsrt_fd("Error: Must provide delimiter for heredoc!\n", 2);
		return (g_signal = 258, 1);
	}
	file_name = create_file((*tk_lst)->val, HEREDOC, NULL);
	if (!file_name)
		return (1);
	add_file_to_list(&new_cmd->redir, file_name);
	return (0);
}

int	flag_redir(t_token **tk_lst, t_cmd *new_cmd)
{
	t_type	type;
	t_redir	*file_name;

	type = (*tk_lst)->type;
	if (!(*tk_lst)->next)
	{
		printf("Minishell: Syntax error: Unexpected token '%c' found. 
			Please review your command and try again.\n", (*tk_lst)->type);
		return (g_signal = 258, 1);
	}
	*tk_lst = (*tk_lst)->next;
	if (!(*tk_lst) || (*tk_lst)->type != WORD)
	{
		printf("Minishell: Syntax error: Unexpected token '%c' found. 
			Please review your command and try again.\n", (*tk_lst)->type);
		return (g_signal = 258, 1);
	}
	file_name = create_file(NULL, type, (*tk_lst)->val);
	if (!file_name)
		return (1);
	add_file_to_list(&new_cmd->redir, file_name);
	return (0);
}

char	*redir_handling(char *input)
{
	char	*new_str;
	char	*tmp;

	tmp = put_begin_space(input, 0);
	if (!tmp)
		return (free(input), NULL);
	free(input);
	new_str = put_end_space(tmp, 0);
	if (!new_str)
		return (free(tmp), NULL);
	free(tmp);
	return (new_str);
}

/*t_redir *make_redir_node(char *file_name, t_type type)
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
	t_redir	*redir_head;
	t_redir	*redir_cur;
	char	*word;
	bool	redir;
	t_type	type;
	
	redir = false;
	start_redir(&redir_head, &redir_cur);
	word = ft_strtok_rm_quotes(msg, prompt->whitespace);
	while (word != NULL)
	{
		if (is_redir_operator(word))
		{
			redir = true;
			type = find//build a list for the redirection tokens
	// check if redirection operator is in word
	// flag if it found as true
} */
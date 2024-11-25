

#include "../lib/minishell.h"

static int	handle_heredoc_special_case(t_token **cur_token,
			t_token **prev_token)
{
	if ((*cur_token)->next
		&&get_token_type((*cur_token)->next->val) == HEREDOC)
	{
		*prev_token = *cur_token;
		*cur_token = (*cur_token)->next;
		*prev_token = *cur_token;
		*cur_token = (*cur_token)->next;
		return (1);
	}
	return (0);
}

t_redir	*process_redirection_token(t_token *cur_token, t_token **prev_token)
{
	int		file_type;
	t_redir	*redir_lst;
	t_token	*new_cur_token;

	file_type = determine_file_type(cur_token);
	redir_lst = NULL;
	new_cur_token = NULL;
	if (file_type != -1)
	{
		if (file_type == HEREDOC_INPUT)
		{
			new_cur_token = cur_token;
			handle_heredoc(cur_token, &new_cur_token, prev_token, file_type);
			if (new_cur_token != NULL)
				add_to_redir_lst(new_cur_token, &redir_lst,
					file_type, *prev_token);
		}
		else if (cur_token->next
			&& get_token_type(cur_token->next->val) == WORD)
		{
			add_to_redir_lst(cur_token->next, &redir_lst, file_type, cur_token);
		}
	}
	return (redir_lst);
}

static bool	is_valid_starting_token(t_token *token_lst)
{
	return (token_lst != NULL && get_token_type(token_lst->val) == WORD);
}

static void	process_token_and_add_redir(t_token **cur_token,
			t_token **prev_token, t_redir **redir_lst)
{
	t_redir	*new_redir;

	new_redir = NULL;
	if (get_token_type((*cur_token)->val) == HEREDOC)
	{
		if (handle_heredoc_special_case(cur_token, prev_token))
			return ;
	}
	new_redir = process_redirection_token(*cur_token, prev_token);
	if (new_redir)
	{
		new_redir->next = *redir_lst;
		*redir_lst = new_redir;
	}
	*prev_token = *cur_token;
	*cur_token = (*cur_token)->next;
}

t_redir	*create_redir_lst_from_tokens(t_token *token_lst)
{
	t_token	*cur_token;
	t_token	*prev_token;
	t_redir	*redir_lst;

	cur_token = token_lst;
	prev_token = NULL;
	redir_lst = NULL;
	if (!is_valid_starting_token(token_lst))
		return (NULL);
	while (cur_token != NULL)
		process_token_and_add_redir(&cur_token, &prev_token, &redir_lst);
	return (redir_lst);
}

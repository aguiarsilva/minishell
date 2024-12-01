/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 23:16:49 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/12/01 23:16:49 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

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

t_redir	*create_redir_lst_from_tokens(t_token *token_lst)
{
	t_token	*cur_token;
	t_token	*prev_token;
	t_redir	*redir_lst;
	t_redir	*last_redir;
	t_redir	*new_redir;

	cur_token = token_lst;
	prev_token = NULL;
	redir_lst = NULL;
	last_redir = NULL;
	while (cur_token != NULL)
	{
		new_redir = process_redirection_token(cur_token, &prev_token);
		append_redir_node(&redir_lst, &last_redir, new_redir);
		prev_token = cur_token;
		cur_token = cur_token->next;
	}
//	print_redir_list(redir_lst); // DEBUG
	return (redir_lst);
}

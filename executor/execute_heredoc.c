/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:59:14 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/11/27 13:59:14 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static void	rm_newline(char **str)
{
	size_t	i;

	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	(*str)[i] = '\0';
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

static int	create_heredoc(t_token *token_list)
{
	int		fd_temp;
	char	*buf[2];
	t_token	*delimit;

	if (token_list->next != NULL)
		delimit = token_list->next;
	fd_temp = open("temp0", O_RDWR | O_CREAT | O_TRUNC, 00644);
	if (fd_temp == -1)
		return (1);
	while (1)
	{
		write(0, "> ", 2);
		buf[0] = get_next_line(STDIN_FILENO);
		if (!buf[0])
			return (1);
		rm_newline(&buf[0]);
		if (ft_memcmp(delimit->val, buf[0], ft_strlen(delimit->val) + 1) == 0)
			break ;
		ft_putstr_fd_mod(buf[0], fd_temp);
		free(buf[0]);
	}
	free(buf[0]);
	return (close(fd_temp), 0);
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

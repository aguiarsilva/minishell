

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
	char	*filename;
	t_token	*delimit_node;

	if (token_list->next != NULL)
	{
		delimit_node = token_list->next;
//		fprintf(stderr, "next_node_val: %s\n", delimit_node->val);
	}
	else
		fprintf(stderr, "next node is NULL\n");
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

void	handle_heredoc(t_token *cur_token, t_token **next_token,
			t_token **prev_token, int file_type)
{
	t_token	*file_token;

	file_token = NULL;
	if (file_type == HEREDOC_INPUT)
	{
		if (*prev_token != NULL)
		{
			printf("in handle doc prev_token = %s, cur_token = %s\n",
				(*prev_token)->val, cur_token->val);
		}
		create_heredoc(cur_token);
		file_token = make_token("temp0", WORD);
		insert_token_between(cur_token, file_token);
		*next_token = file_token->next;
		*prev_token = file_token;
	}
}

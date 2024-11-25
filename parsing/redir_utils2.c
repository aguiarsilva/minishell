//
//#include "../lib/minishell.h"
//
//int	check_no_space_redir_excl_special(char *input)
//{
//	int	no_space;
//	int	i;
//
//	no_space = 0;
//	i = -1;
//	while (input[++i])
//	{
//		skip_quotes_without_copy(input, &i);
//		if (i > 0 && (input[i] == '<' || input[i] == '>' || input[i] == '|')
//			&& input[i - 1] != 26)
//		{
//			no_space++;
//			if ((input[i] == '<' && input [i + 1] == '>')
//				|| (input[i] == '>' && input[i + 1] == '<')
//				|| (input[i - 1] == '<' || input [i - 1] == '>'))
//				no_space--;
//		}
//	}
//	return (no_space);
//}
//
//void	copy_and_skip_quotes(char *str, int *i, char **input, int *j)
//{
//	char	temp;
//
//	temp = '\0';
//	if (str[*i] == '"' || str[*i] == '\'')
//	{
//		temp = str[*i];
//		(*input)[(*j)++] = str[*i];
//		(*i)++;
//		while (str[*i] && str[*i] != temp)
//		{
//			(*input)[(*j)++] = str[*i];
//			(*i)++;
//		}
//	}
//}
//
//void	skip_quotes_without_copy(char *str, int *i)
//{
//	char	temp;
//
//	temp = '\0';
//	if (str[*i] == '"' || str[*i] == '\'')
//	{
//		temp = str[*i];
//		(*i)++;
//		while (str[*i] && str[*i] != temp)
//			(*i)++;
//	}
//}

//#include "../lib/minishell.h"
//
//void	add_file_to_list(t_redir **lst, t_redir *file_name)
//{
//	t_redir	*nptr;
//
//	nptr = lst;
//	while (*lst)
//		nptr = &(*nptr)->next;
//	*nptr = file_name;
//}
//
//t_redir	*create_file(char *delimiter, t_type type, char *file_name)
//{
//	t_redir	*node;
//
//	node = (t_redir *)malloc(sizeof(*node));
//	if (!node)
//		return (NULL);
//	ft_bzero(node, sizeof(*node));
//	if (file_name)
//	{
//		node->file_name = ft_strdup(file_name);
//		if (!node->file_name)
//			return (NULL);
//	}
//	if (delimiter)
//	{
//		node->delim = ft_strdup(delimiter);
//		if (!node->delim)
//			return (NULL);
//	}
//	node->type = type;
//	node->next = NULL;
//	return (node);
//}
//
//char	*put_begin_space(char *str, int i)
//{
//	int		j;
//	char	*input;
//	int		no_space;
//
//	j = -1;
//	no_space = check_no_space_redir_excl_special(str);
//	input = ft_calloc((ft_strlen(str) + no_space + 1), sizeof(char));
//	if (!input)
//		return (NULL);
//	while (str[++j])
//	{
//		copy_and_skip_quotes(str, &j, &input, &i);
//		if(j > 0 && (str[j] == '<' || str[j] == '>' || str[j] == '|')
//			&& str[j - 1] != 26)
//		{
//			input[i++] = 26;
//			if ((str[j] == '<' && str[j + 1] == '>')
//			|| (str[j] == '>' && str[j + 1] == '<')
//			|| (str[j - 1] == '<' || str[j - 1] == '>'))
//			j--;
//		}
//		input[i++] = str[j];
//	}
//	return (input);
//}
//
//char	*put_end_space(char *str, int i)
//{
//	int		j;
//	char	*input;
//	int		no_space;
//
//	j = -1;
//	no_space = check_no_space_redir_next(str);
//	input = ft_calloc((ft_strlen(str) + no_space + 1), sizeof(char));
//	if (!input)
//		return (NULL);
//	while (str[++j])
//	{
//		copy_and_skip_quotes(str, &j, &input, &i);
//		if(j > 0 && (str[j] == '<' || str[j] == '>' || str[j] == '|')
//			&& str[j - 1] != 26)
//		{
//			input[i++] = 26;
//			if ((str[j] == '<' && str[j + 1] == '>')
//			|| (str[j] == '>' && str[j + 1] == '<')
//			|| (str[j - 1] == '<' || str[j - 1] == '>'))
//			j--;
//		}
//		input[i++] = str[j];
//	}
//	return (input);
//}
//
//int	check_no_space_redir_next(char *input)
//{
//	int	no_space;
//	int	i;
//
//	no_space = 0;
//	i = -1;
//	while (input[++i])
//	{
//		skip_quotes_without_copy(input, &i);
//		if ((input[i] == '<' || input[i] == '>' || input[i] == '|')
//			&& (input[i + 1] != '<' && input[i + 1] != '>'
//			&& input [i + 1] != 26 && input[i + 1]))
//		{
//			no_space++;
//			if (i > 0 && ((input[i] == '<' && input[i - 1] == '>')
//				|| (input[i] == '>' && input[i - 1] == '<')))
//				no_space--;
//		}
//	}
//	return (no_space);
//}

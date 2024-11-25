

#include "../lib/minishell.h"

// bool	is_quoted(const char* input)
// {
// 	int	len;

// 	len = strlen(input);
// 	if (len < 2)
// 		return (false);

// 	// Check if first and last characters are matching quotes
// 	if ((input[0] == '\'' && input[len - 1] == '\'') ||
// 		(input[0] == '"' && input[len - 1] == '"'))
// 		return (true);

// 	return (false); // Not properly quoted
// }

//void	append_node(t_token** head, t_token** curr, t_token* new)
//{
//	if (*head == NULL)
//	{
//		*head = new;
//		*curr = new;
//	}
//	else
//	{
//		(*curr)->next = new;
//		*curr = new;
//	}
//}
//
//void	nodes_init(t_token** head, t_token** cur, t_token** new)
//{
//	*head = NULL;
//	*cur = NULL;
//	*new = NULL;
//}

// int	skip_whitespace(const char *input, int i, int len)
// {
// 	while (i < len && ft_isspace(input[i]))
// 		i++;
// 	return (i);
// }
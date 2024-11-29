/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 02:07:37 by baguiar-          #+#    #+#             */
/*   Updated: 2024/11/29 02:07:48 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	is_quote_character(char c)
{
	return (c == '"' || c == '\'');
}

void	update_quote_state(int *in_quotes, char *quote_type,
		char current_char, int *was_quoted)
{
	if (!(*in_quotes))
	{
		*in_quotes = 1;
		*quote_type = current_char;
		*was_quoted = 1;
	}
	else
	{
		*in_quotes = 0;
		*quote_type = 0;
	}
}

int	should_keep_char(char c, int in_quotes, char quote_type)
{
	return (!is_quote_character(c)
		|| (in_quotes && quote_type != c));
}

void	remove_quotes(char *str, int *was_quoted)
{
	int		i;
	int		j;
	int		in_quotes;
	char	quote_type;

	i = 0;
	j = 0;
	in_quotes = 0;
	quote_type = 0;
	if (!str)
		return ;
	*was_quoted = 0;
	while (str[i] != '\0')
	{
		if (is_quote_character(str[i])
			&& (!in_quotes || quote_type == str[i]))
			update_quote_state(&in_quotes, &quote_type,
				str[i], was_quoted);
		else if (should_keep_char(str[i], in_quotes, quote_type))
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

int	check_for_unmatched_quotes(char *input, int input_length)
{
	int		i;
	char	current_quote;

	i = 0;
	current_quote = 0;
	while (i < input_length)
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			// If no quote is open, this is the opening quote
			if (current_quote == 0)
				current_quote = input[i];
			// If the same quote is encountered again, it's a closing quote
			else if (current_quote == input[i])
				current_quote = 0;
			// If a different type of quote is encountered, it's an error
			else
				return (-1);  // Unexpected quote, return error
		}
		i++;
	}
	if (current_quote != 0)
		return (-1);
	return (0);
}

// void	remove_quotes(char *str, int *was_quoted)
// {
// 	int		i;
// 	int		j;
// 	int		in_quotes;
// 	char	quote_type;

// 	i = 0;
// 	j = 0;
// 	in_quotes = 0;
// 	quote_type = 0;
// 	if (!str)
// 		return ;
// 	*was_quoted = 0;
// 	while (str[i] != '\0')
// 	{
// 		if ((str[i] == '"' || str[i] == '\'')
// 			&& (!in_quotes || quote_type == str[i]))
// 		{
// 			*was_quoted = 1;
// 			if (!in_quotes)
// 			{
// 				in_quotes = 1;
// 				quote_type = str[i];
// 			}
// 			else
// 			{
// 				in_quotes = 0;
// 				quote_type = 0;
// 			}
// 		}
// 		else
// 			str[j++] = str[i];
// 		i++;
// 	}
// 	str[j] = '\0';
// }

//void	remove_quotes(char *str, int *was_quoted) // before big change to handle quotes to keep them together for example echo 'test test2' would split in 3 token
//{
//	int		i;
//	int		j;
//	int		in_quotes;
//	char	quote_type;
//
//	i = 0;
//	j = 0;
//	in_quotes = 0;
//	quote_type = 0;
//	if (!str)
//		return ;
//	*was_quoted = 0;
//	while (str[i] != '\0')
//	{
//		if ((str[i] == '"' || str[i] == '\'')
//			&& (!in_quotes || quote_type == str[i]))
//		{
//			*was_quoted = 1;
//			handle_quote(&in_quotes, &quote_type, str[i]);
//		}
//		else
//			str[j++] = str[i];
//		i++;
//	}
//	str[j] = '\0';
//}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:12:59 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/11 14:40:24 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: split string, with specified character as delimiter, into an array
**			of strings
**
** DESCRIPTION:
** 		Allocates (with malloc(3)) and returns an array of strings obtained by
**	splitting ’s’ using the character ’c’ as a delimiter. The array must be
**	ended by a NULL pointer.
*/

#include "libft.h"

static	size_t	ft_count_word(char const *s, char c)
{
	size_t	cursor_index;
	size_t	word_counter;

	cursor_index = 0;
	word_counter = 0;
	while (s != 0 && s[cursor_index] != '\0')
	{
		if (s[cursor_index] == c)
			cursor_index++;
		else
		{
			word_counter++;
			while (s[cursor_index] != c && s[cursor_index] != '\0')
				cursor_index++;
		}
	}
	return (word_counter);
}

static	size_t	ft_word_size(char const *s, char c)
{
	size_t	word_size;
	size_t	index;

	word_size = 0;
	index = 0;
	while (s[index] != c && s[index] != '\0')
	{
		word_size++;
		index++;
	}
	return (word_size);
}

static	void	ft_free(char **str_array, size_t array_index)
{
	while (array_index-- > 0)
		free(str_array[array_index]);
	free(str_array);
}

char	**ft_split(char const *s, char c)
{
	size_t	word_counter;
	char	**str_array;
	size_t	array_index;

	word_counter = ft_count_word(s, c);
	array_index = 0;
	str_array = (char **)malloc((word_counter + 1) * sizeof(char *));
	if (!str_array)
		return (0);
	while (word_counter--)
	{
		while (*s == c)
			s++;
		str_array[array_index] = ft_substr(s, 0, ft_word_size(s, c));
		if (!str_array[array_index])
		{
			ft_free(str_array, array_index);
			return (0);
		}
		array_index++;
		s += ft_word_size(s, c);
	}
	str_array[array_index] = 0;
	return (str_array);
}

// int	main(void)
// {
// 	char	*s = "  tripouille  42  ";
// 	char	c = ' ';

// 	char **str_array = ft_split(s, c);
// 	if (str_array == NULL)
// 	{
// 		ft_printf("Memory allocation failed\n");
// 		return (1);
// 	}

// 	int	i = 0;
// 	while (str_array[i] != NULL)
// 	{
// 		ft_printf("%s\n", str_array[i]);
// 		i++;
// 	}

// 	// Don't forget to free the memory allocated by ft_split
// 	i = 0;
// 	while (str_array[i] != NULL)
// 	{
// 		free(str_array[i]);
// 		i++;
// 	}
// 	free(str_array);

//     return 0;
// }

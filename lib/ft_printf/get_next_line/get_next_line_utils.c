/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:20:19 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/02/23 18:14:02 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc_complete(size_t count, size_t size)
{
	void				*ptr;
	size_t				tot_size;
	unsigned char		*temp;

	tot_size = count * size;
	if (count && size != (tot_size / count))
		return (NULL);
	ptr = malloc(tot_size);
	if (!ptr)
	{
		return (0);
	}
	temp = ptr;
	while (tot_size--)
		*temp++ = 0;
	return (ptr);
}

char	*ft_strchr_duplicate(const char *s, int c)
{
	while (*s != '\0' && (unsigned char)c != *s)
		s++;
	if ((unsigned char)c == *s)
		return ((char *)s);
	return (0);
}

char	*initialize_line_read_if_null(char *line_read)
{
	char	*tmp;

	if (!line_read)
	{
		tmp = ft_calloc_complete(1, sizeof(char));
		if (!tmp)
			return (NULL);
		line_read = tmp;
	}
	return (line_read);
}

//size_t	ft_strlen(const char *s)
//{
//	size_t	strlen;
//
//	strlen = 0;
//	while (s[strlen] != '\0')
//	{
//		strlen++;
//	}
//	return (strlen);
//}

size_t	find_newline_pos(const char *str)
{
	size_t	char_index;

	char_index = 0;
	while (str[char_index] && str[char_index] != '\n')
		char_index++;
	return (char_index);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:40:52 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/11 14:44:07 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: trim beginning and end of string with the specified characters
**
** DESCRIPTION:
** 		Allocates (with malloc(3)) and returns a copy of ’s1’ with the
**	characters specified in ’set’ removed from the beginning and the end of the
**	string.
*/

#include "libft.h"

int	ft_getstart(const char *s1, const char *set)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	while (i < len)
	{
		if (ft_strchr_duplicate(set, s1[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

int	ft_getend(const char *s1, const char *set)
{
	size_t	len;
	size_t	i;
	size_t	final_end;

	len = ft_strlen(s1);
	i = 0;
	while (i < len)
	{
		if (ft_strchr_duplicate(set, s1[len - i - 1]) == 0)
			break ;
		i++;
	}
	final_end = len - i;
	return (final_end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*trimmed_str;

	if (s1 == 0)
		return (0);
	if (set == 0)
		return (ft_strdup(s1));
	start = ft_getstart(s1, set);
	end = ft_getend(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	trimmed_str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (trimmed_str == 0)
		return (0);
	ft_strlcpy(trimmed_str, s1 + start, end - start + 1);
	return (trimmed_str);
}

// ft_getstart, checks if the current pointer of s1 matches with one character
// in the set string from left to right.
// If they match increase i and check next character
// otherwise return the current pointer position i
// ft_getend, does the same but from right to left

// int main(void)
// {
//     char *s1 = "  Hello, World!  ";
//     char *set = " ";

//     char *trimmed_str = ft_strtrim(s1, set);
//     if (trimmed_str == NULL)
//     {
//         ft_printf("Memory allocation failed\n");
//         return 1;
//     }

//     ft_printf("%s\n", trimmed_str);

//     // Don't forget to free the memory allocated by ft_strtrim
//     free(trimmed_str);

//     return 0;
// }

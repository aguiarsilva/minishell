/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:21:58 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/11 14:43:28 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <string.h>
** SYNOPSIS: compare strings
**
** DESCRIPTION:
** 		The strcmp() and strncmp() functions lexicographically compare the null-
**	terminated strings s1 and s2.
*/

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	if (n == 0)
	{
		return (0);
	}
	while (index < n && (*s1 || *s2))
	{
		if (*s1 != *s2)
			return ((unsigned char )*s1 - (unsigned char )*s2);
		index++;
		s1++;
		s2++;
	}
	return (0);
}

// int	main(void)
// {
// 	char	str1[] = "tenet";
// 	char	str2[] = "benet";
// 	int		c = 6;
// // 	int result = strncmp(str1, str2, 3);
// // 	if (result == 0) {
// // 	ft_printf("The strings are equal\n");
// // 	} else if (result < 0) {
// // 	ft_printf("The first string is lexicographically
// // less than the second\n");
// // 	} else {
// // 	ft_printf("The first string is lexicographically greater
// // than the second\n");
// // 	}
// 	ft_printf("ori %d|\n", strncmp(str1, str2, c));
// 	ft_printf("my  %d|", ft_strncmp(str1, str2, c));
// }
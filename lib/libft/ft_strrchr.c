/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:51:19 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/11 14:43:51 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <string.h>
** SYNOPSIS: locate character in string (last occurence)
**
** DESCRIPTION:
** 		The strrchr() function locates the last occurrence of c (converted to a
**	char) in the string s.  If c is `\0', strrchr() locates the terminating
**	`\0'.
*/

#include "libft.h"

// char	*ft_strrchr(const char *s, int c)
// {
// 	while (*s != '\0')
// 	{
// 		s++;
// 	}
// 	while ((unsigned char)c != *s)
// 		s--;
// 	if ((unsigned char)c == *s)
// 		return ((char *)s);
// 	return (0);
// }
char	*ft_strrchr(const char *s, int c)
{
	char	*lastseen;

	lastseen = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			lastseen = (char *)s;
		}
		s++;
	}
	if (*s == (char)c)
		lastseen = (char *)s;
	return ((char *)lastseen);
}

// typecast from int to char is needed because if c
// is larger than the maximum value that can be represented by a char
// (for signed char 127 / for unsigned char 255)
// the value of c would be automatically converted to a negative number 
// when it is compared with a char. This is called type coercion
// The typecast tells the compiler to treat c as a char or unsigned char
// when it is used in the comparison,
// so the comparison will be done between values of the same type.

// int	main(void)
// {
// 	char	str[6] = "tenet";
// 	int		c = '\0';

// 	ft_printf("original %s|\n", strrchr(str, c));
// 	ft_printf("my %s|", ft_strrchr(str, c));
// }
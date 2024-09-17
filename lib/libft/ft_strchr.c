/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:51:19 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/11 14:42:14 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <string.h>
** SYNOPSIS: locate character in string (first occurrence)
**
** DESCRIPTION:
** 	The strchr() function locates the first occurrence of c (converted to a
**	char) in the string pointed to by s.  The terminating null character is
**	considered to be part of the string; therefore if c is `\0', the func-
**	tions locate the terminating `\0'.
*/

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0' && (unsigned char)c != *s)
		s++;
	if ((unsigned char)c == *s)
		return ((char *)s);
	return (0);
}

/*typecast from int to char is needed because if c
is larger than the maximum value that can be represented by a char
(for signed char 127 / for unsigned char 255)
the value of c would be automatically converted to a negative number
when it is compared with a char. This is called type coercion
The typecast tells the compiler to treat c as a char or unsigned char
when it is used in the comparison,
so the comparison will be done between values of the same type.*/
// int	main(void)
// {
// 	char	str[6] = "hello";

// 	//search for an existing character in string
// 	ft_printf("%s\n", ft_strchr(str, 'h'));

// 	//search for not an existing character in string
// 	ft_printf("%s\n", ft_strchr(str, 'i'));

// 	return (0);

// }
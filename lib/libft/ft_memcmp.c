/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:55:18 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/20 14:32:34 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <string.h>
** SYNOPSIS: compare byte string
**
** DESCRIPTION:
** 		The memcmp() function compares byte string s1 against byte string s2.
**	Both strings are assumed to be n bytes long.
*/

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				index;
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = s1;
	str2 = s2;
	index = 0;
	if (n == 0)
	{
		return (0);
	}
	while (index < n)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		index++;
		str1++;
		str2++;
	}
	return (0);
}

// int	main(void)
// {
// 	ft_printf("%d\n", ft_memcmp("t\200", "t\0", 5));
// 	ft_printf("%d", memcmp("t\200", "t\0", 5));
// }

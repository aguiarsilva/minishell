/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:27:08 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/20 15:43:22 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <string.h>
** SYNOPSIS: locate a substring in a string (size-bounded)
**
** DESCRIPTION:
** 	The strnstr() function locates the first occurrence of the null-termi-
**	nated string s2 in the string s1, where not more than n characters are
**	searched.  Characters that appear after a `\0' character are not
**	searched.
*/

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	haystack_len;
	size_t	i;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)(haystack));
	needle_len = ft_strlen(needle);
	haystack_len = ft_strlen(haystack);
	if (haystack_len == 0)
	{
		if (needle_len == 0)
			return ((char *)(haystack));
		else
			return (0);
	}
	while (haystack[i] != '\0' && (i + needle_len) <= len)
	{
		if (ft_strncmp(haystack + i, needle, needle_len) == 0)
			return ((char *)(haystack + i));
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	const char *largestring = "Foo Bar Baz";
// 	const char *smallstring = "Bar";
// 	char *ptr;
// 	char *ptr2;

// 	// ptr = strnstr(largestring, smallstring, 3);
// 	ptr2 = ft_strnstr(largestring, smallstring, 7);
// 	// should print Bar Baz when len >= 7

// 	// ft_printf("ori|:  %s\n", ptr);
// 	ft_printf("my %s\n", ptr2);

// 	return (0);
// }

// edgecase
// int    main(void)
// {
//     const char *largestring = "lorem ipsum dolor sit amet";
//     const char *smallstring = "dolor";
//     char *ptr;
//     char *ptr2;

//     // ptr = strnstr(largestring, smallstring, 3);
//     ptr2 = ft_strnstr(largestring, smallstring, 15);

//     // ft_printf("ori|:  %s\n", ptr);
//     ft_printf("my %s\n", ptr2);

//     return (0);
// }
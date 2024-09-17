/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:41:03 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/04 15:58:52 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: extract substring from string
**
** DESCRIPTION:
** 		Allocates (with malloc(3)) and returns a substring from the string ’s’.
**	The substring begins at index ’start’ and is of maximum size ’len’.
*/

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	remainder_size;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	remainder_size = ft_strlen(s + start);
	if (remainder_size < len)
		len = remainder_size;
	substring = malloc(sizeof(char) * (len + 1));
	if (!substring)
	{
		return (0);
	}
	ft_strlcpy(substring, s + start, len + 1);
	return (substring);
}

// Second if needed when the start
// is after the end of the whole string
// the variable remainder_size is needed
// to determine how big the remainder of s is.
// The 'remaider_size' variable represents 
// the remaider_size of the substring being returned,
// which is equal to the length of the string starting at the start index
// The 'len' variable represents the maximum length
// of the substring that should be returned
// the third if is needed when remaider_size < len
// it means that the entire remainder of the string
// starting at start should be returned,
// so len should be set to remaider_size in order to ensure
// that the entire remainder of the string is returned

// int	main(void)
// {
// 	char	string[] = "Save all the cats";
// 	char	*substring;

// 	// substring = ft_substr(string, 0, 10);
// 	substring = ft_substr("hola", 0, 18446744073709551615);
// 	ft_printf("%s", substring);
// 	free(substring);
// 	return (0);
// }

// old version
// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*substring;
// 	size_t	s_len;

// 	if (!s)
// 		return (0);
// 	s_len = strlen(s);
// 	if (start > s_len)
// 		return (strdup(""));
// 	if (len > s_len - start)
// 		len = s_len - start;
// 	substring = malloc(len + 1);
// 	if (!substring)
// 	{
// 		return (0);
// 	}
// 	memcpy(substring, s + start, len);
// 	substring[len] = '\0';
// 	return (substring);
// }
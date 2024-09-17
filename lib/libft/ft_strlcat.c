/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 13:39:13 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/20 15:22:42 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <string.h>
** SYNOPSIS: size-bounded string concatenation
**
** DESCRIPTION:
** 	The strlcpy() and strlcat() functions copy and concatenate strings
**	respectively. Strlcat() take the full size of the buffer (not
**	just the length) and guarantee to NUL-terminate the result (as long as
**	size is larger than 0 or, as long as there is at least one byte free in dst).
**	For strlcat() both src and dst must be NUL-terminated.
** 	The strlcat() function appends the NUL-terminated string src to the end
**	of dst.  It will append at most size - strlen(dst) - 1 bytes, NUL-termi
**	nating the result.
*/
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	maxcopylen;
	size_t	index;

	maxcopylen = 0;
	index = 0;
	while (dst[maxcopylen] != '\0' && maxcopylen < size)
		maxcopylen++;
	while (src[index] != '\0' && (maxcopylen + index + 1) < size)
	{
		dst[maxcopylen + index] = src[index];
		index++;
	}
	if (maxcopylen < size)
		dst[maxcopylen + index] = '\0';
	return (maxcopylen + ft_strlen(src));
}
// maxcopylen means how many bytes can be copied from dst,
// it always has to be smaller than size to have space for
// the null terminator
// in while loop + 1 is needed when there is not enough space for 
// the characters to copy from src to the end of dst. It ensures 
// that there is room for the null terminator in the end.
// last if is needed when you don't copy the whole string from src
// that could lead to a missing null terminator 

// no idea why this is wrong
// size_t	ft_strlcat(char *dst, const char *src, size_t size)
// {
// 	size_t	dstlen;

// 	dstlen = 0;
// 	if (size == 0)
// 		return (strlen(src));
// 	while (*dst != '\0')
// 	{
// 		dst++;
// 		dstlen++;
// 	}
// 	*dst = '\0';
// 	while (*src && size > 1)
// 	{
// 		*dst++ = *src++;
// 		size--;
// 	}
// 	return (dstlen + strlen(src));
// }

// int main(void) {
//   char dest[20] = "Hello, ";
//   char src[] = "world!";

//   // Test strlcat with destination buffer larger than required
//   size_t dest_len = ft_strlcat(dest, src, 20);
//   ft_printf("strlcat result: %s, length: %zu\n", dest, dest_len);

//   // Test strlcat with destination buffer smaller than required
//   char dest2[20] = "Hello, ";
//   size_t dest2_len = ft_strlcat(dest2, src, 5);
//   ft_printf("strlcat result: %s, length: %zu\n", dest2, dest2_len);

//   return 0;
// }

// example for +1 case
// int main(void) {
//   char dest[6] = "cat";
//   char src[] = "dog";

//   // Test strlcat with destination buffer just large enough for the string
//   but no space for the null terminator 
//   size_t dest_len = ft_strlcat(dest, src, 6);
//   ft_printf("strlcat result: %s, length: %zu\n", dest, dest_len);

//   return 0;
// }
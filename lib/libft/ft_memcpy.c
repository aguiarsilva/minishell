/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:24:55 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/20 15:22:42 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <string.h>
** SYNOPSIS: copy string until character found
**
** DESCRIPTION:
** 	The memccpy() function copies bytes from string s2(src) to string s1(dst).
**	If thecharacter c (as converted to an unsigned char) occurs in the string s2,
**	the copy stops and a pointer to the byte after the copy of c in the
**	string s1 is returned. Otherwise, n bytes are copied, and a NULL pointer
**	is returned.
*/

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dstp;
	unsigned char	*srcp;

	if (!dst && !src)
		return (0);
	if (n > 0)
	{
		dstp = (unsigned char *)dst;
		srcp = (unsigned char *)src;
		while (n-- > 0)
		{
			*dstp++ = *srcp++;
		}
	}
	return (dst);
}

// int main() {
// 	char src[] = "Hello, world!";
// 	char dest[20];

// //copy src to dest using memcpy
// 	ft_memcpy(dest, src, ft_strlen(src) + 1);
// 	ft_printf("my: |dest after memcpy: %s\n", dest);

// //copy src to dest again, but this time overlap the memory regions
//   while loop gets outside of memory location
// 	ft_memcpy(src + 5, src, ft_strlen(src) + 1);
// 	ft_printf("my: |src after overlapping memcpy: %s\n", src);

// // //don't do both memcpy and memmove it will crash

// // copy src to dest again, but this time overlap the memory regions
//   memmove(src + 5, src, ft_strlen(src) + 1);
//   ft_printf("src after overlapping memmove: %s\n", src);

// // dst smalller than src, result should be nothing returns
// 	char src2[] = "Hello, world!" ;
// 	char dst2[5];
// 	ft_memcpy(dst2, src2, 13);
//   return 0;
// }
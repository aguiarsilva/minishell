/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:21:38 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/20 15:22:42 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <string.h>
** SYNOPSIS: copy byte string
**
** DESCRIPTION:
** 	The memmove() function copies n bytes from string s2 to string s1.  The
**	two strings may overlap; the copy is always done in a non-destructive
**	manner.
*/

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dstp;
	unsigned char	*srcp;

	if (!dst && !src)
		return (0);
	dstp = (unsigned char *)dst;
	srcp = (unsigned char *)src;
	if (dst < src)
	{
		ft_memcpy(dst, src, len);
	}
	else
	{
		srcp += len -1;
		dstp += len -1;
		while (len-- > 0)
			*dstp-- = *srcp--;
	}
	return (dst);
}
/*basic idea instead copying from left to right, copy right to left */
// int main(void) {
// 	char	src[] = "Hello, world!";
// 	char	dest[20];
// 	char	too_small_dest[5];

// //	copy src to dest using memmove
// 	ft_memmove(dest, src, ft_strlen(src) + 1);
// 	ft_printf("dest after memmove: %s\n", dest);

// //	copy src to dest again, but this time overlap the memory regions
// 	ft_memmove(src + 5, src, ft_strlen(src) + 1);
// 	ft_printf("src after overlapping memmove: %s\n", src);

// //	copy a zero-length block of memory, should return nothing
// 	ft_memmove(dest, src, 0);
// 	ft_printf("dest after memmove: %s\n", dest);

// //	dst too small to hold src, how to handle?
// 	ft_memmove(too_small_dest, src, 13*sizeof(char));
// 	ft_printf("dest after memmove: %s\n", too_small_dest);

// 	return 0;
// }

//works aswell
// void	*ft_memmove(void *dst, const void *src, size_t len)
// {
// 	unsigned char	*dstp;
// 	unsigned char	*srcp;

// 	if (!dst && !src)
// 		return (0);
// 	dstp = (unsigned char *)dst;
// 	srcp = (unsigned char *)src;
// 	if (dst < src)
// 	{
// 		while (len-- > 0)
// 			*dstp++ = *srcp++;
// 	}
// 	else
// 	{
// 		srcp += len;
// 		dstp += len;
// 		while (len-- > 0)
// 			*--dstp = *--srcp;
// 	}
// 	return (dst);
// }
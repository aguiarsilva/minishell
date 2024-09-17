/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:12:00 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/03 12:57:58 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <string.h>
** SYNOPSIS: write a byte to a byte string
**
** DESCRIPTION:
** 	The memset() function writes n bytes of value c (converted to an
**	unsigned char) to the string s.
*/

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr_p;

	ptr_p = b;
	while (len-- > 0)
	{
		*ptr_p++ = (unsigned char)c;
	}
	return (b);
}
/* why does it have a return value when it is a void function?
this function returns a pointer to a memory location
but the type of the data stored at that location is not specified.
C allows that the caller can treat a memory block like an array of any type
We have to return b because otherwise
we could not access the new filled memory block  */

/* b means pointer to memoryblock to overwrite*/
/* c means the value/sign to be written to the memory block */
/* len the number of bytes to be written*/
/* source https://www.proggen.org/doku.php?id=c:lib:string:memset*/

// int	main(void)
// {
// 	char str[50] = "GeeksForGeeks is for programming geeks.";
// 	ft_printf("\nBefore memset(): %s\n", str);

// 	//Fill 8 characters starting from str[13] with '.'
// 	ft_memset(str + 13, '0', 8*sizeof(char));
// 	ft_printf("After memset():  %s", str);

// 	//Zero-Length block of memory
// 	ft_memset(str + 13, '0', 0 * sizeof(char));
// 	ft_printf("After memset():  %s", str);

// 	// Setting a value that is not a character, should stack smashing
// 	ft_memset(str + 13, 256, 50 * sizeof(char));
// 	ft_printf("After memset():  %s", str);

// 	return (0);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 12:43:56 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/20 15:24:33 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <string.h>
** SYNOPSIS: locate byte in byte string
**
** DESCRIPTION:
** 		The memchr() function locates the first occurrence of c (converted to an
**	unsigned char) in string s.
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr_s;

	if (n == 0)
		return (0);
	ptr_s = (unsigned char *) s;
	while (--n > 0 && (unsigned char)c != *ptr_s)
		ptr_s++;
	if ((unsigned char)c == *ptr_s)
		return ((char *)ptr_s);
	return (0);
}

/* --n is needed because will search through one more character 
** than if i use n--
** with n--: -n operation is performed before the comparison with 0,
** so the loop continues to execute as long as n is greater than 0.
** This means that the loop will execute n times,
** and the value of ptr_s will be incremented n times.
** with n--: the loop continues to execute as long as n is not equal to 0.
** This means that the loop will execute n - 1 times, 
** and the value of ptr_s will be incremented n - 1 times.
*/

// int	main () {
// 	const 	char str[] = "bonjourno";
// 	const 	char c = 'n';
// 	char 	*ret_ori;
// 	char 	*ret_my;

// 	ret_ori = memchr(str, c, 3);
// 	ret_my = ft_memchr(str, c, 3);
// 	// just a basis function test
// 	ft_printf("ori |String after |%c| is - |%s|\n", c, ret_ori);
// 	ft_printf("my  |String after |%c| is - |%s|\n", c, ret_my);

// 	// n = 0 
// 	void *null_ptr = ft_memchr(str, 'x', 0);
// 	if (null_ptr == NULL)
// 		ft_printf("null pointer returned\n");
// 	return(0);

// // searching for a character in string that is 
// // longer than the maximum allowed length
// 	char long_string[] = "This is a very long string";
//   	int max_length = 5;
//   	char* result = ft_memchr(long_string, 'a', max_length);

//   	if (result == NULL) {
// 	ft_printf("Character 'a' was not found in the first
// %d characters of the string.\n", max_length);
// 	} else {
// 	ft_printf("Character 'a' was found at index
// %ld in the string.\n", result - long_string);
// 	}

// 	return (0);

// }
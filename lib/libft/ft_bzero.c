/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:46:32 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/01 20:12:22 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <strings.h>
** SYNOPSIS: write zeroes to a byte string
**
** DESCRIPTION:
** 		The bzero() function writes n zeroed bytes to the string s. If n is
**	zero, bzero() does nothing.
*/

#include "libft.h"

void	*ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
	return (s);
}

// int	main()
// {
// 	char str[50] = "GeeksForGeeks is for programming geeks.";
// 	ft_printf("\nBefore bzero(): %s\n", str);

// 	bzero(str + 13, 1);

// 	ft_printf("orig: After bzero():  %s", str);

// 	char str2[50] = "GeeksForGeeks is for programming geeks.";
// 	ft_printf("\nBefore bzero(): %s\n", str2);

// 	ft_bzero(str2 + 13, 1);

// 	ft_printf("my: After bzero():  %s", str2);

// 	//test large buffer
// 	char	big_buffer[10000];

// 	memset(big_buffer, 'x', sizeof(big_buffer));
// 	ft_printf("before: %s\n", big_buffer);
// 	ft_bzero(big_buffer, sizeof(big_buffer));
// 	ft_printf("after: %s\n", big_buffer);

// 	//test uninitialized buffer
// 	char	big_buffer2[10000];

// 	ft_printf("before: %s\n", big_buffer2);
// 	bzero(big_buffer2, sizeof(big_buffer2));
// 	ft_printf("after: %s\n", big_buffer2);
// 	return (0);

// }
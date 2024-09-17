/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:55:32 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/20 15:50:26 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <string.h>
** SYNOPSIS: save a copy of a string (with malloc)
**
** DESCRIPTION:
** 		The strdup() function allocates sufficient memory for a copy of the
**	string s1, does the copy, and returns a pointer to it.  The pointer may
**	subsequently be used as an argument to the function free(3).
*/

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;

	dest = malloc(ft_strlen(s1)+1);
	if (!dest)
	{
		return (0);
	}
	ft_memcpy(dest, s1, ft_strlen(s1)+1);
	return (dest);
}

// int main(void) 
// {
// 	char *original = "Hello, World!";
// 	char *copy = ft_strdup(original);
// 	if (copy == NULL)
// 	{
// 	// strdup failed
// 		perror("strdup");
// 		return (1);
// 	}

// 	ft_printf("Original string: %s\n", original);
// 	ft_printf("Copy of string: %s\n", copy);
// 	free(copy);
// 	return 0;
// }
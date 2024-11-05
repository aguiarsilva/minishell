/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:13:01 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/11/05 20:13:01 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <string.h>
** SYNOPSIS: concatenate two strings
**
** DESCRIPTION:
** 		Appends the string ’src’ to the end of ’dest’. The destination string
**	must have sufficient space to hold the result. The resulting string in
**	’dest’ is null-terminated and returned by the function.
*/

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	char	*dest_end;

	dest_end = dest;
	while (*dest_end != '\0')
		dest_end++;
	while (*src != '\0')
	{
		*dest_end = *src;
		dest_end++;
		src++;
	}
	*dest_end = '\0';
	return (dest);
}

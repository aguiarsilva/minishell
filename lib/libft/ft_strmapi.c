/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:37:34 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/20 15:22:42 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: create new string from modifying string with specified function
**
** DESCRIPTION:
** 		Applies the function ’f’ to each character of the string ’s’ to create
**	a new string (with malloc(3)) resulting from successive applications of ’f’.
*/

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	int		current_index;
	char	*res;

	current_index = 0;
	len = ft_strlen(s);
	res = (char *) malloc(sizeof(char) * len + 1);
	if (!res)
		return (0);
	while (current_index < len)
	{
		res[current_index] = f(current_index, s[current_index]);
		current_index++;
	}
	res[current_index] = '\0';
	return (res);
}

// int	main(void)
// {
// 	char	* s = ft_strmapi("1234", addOne);
// 	ft_printf("%s", s);
// }
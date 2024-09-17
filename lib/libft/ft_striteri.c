/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:54:04 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/20 14:47:07 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: it modifies the original string 
** with specified function on the index you put in
** DESCRIPTION:
** 		Applies the function ’f’ on each character of
**		the string passed as argument, passing its index
**		as first argument. Each character is passed by
**		address to ’f’ to be modified if necessary.
*/
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		current_index;

	current_index = 0;
	while (s[current_index])
	{
		f(current_index, &s[current_index]);
		current_index++;
	}
}

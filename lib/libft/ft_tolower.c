/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:07:47 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/11 14:44:40 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <ctype.h>
** SYNOPSIS: upper case to lower case letter conversion
**
** DESCRIPTION:
** 		The tolower() function converts an upper-case letter to the
**	corresponding lower-case letter.
*/

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z' )
		return (c + 32);
	return (c);
}

// int main (void)
// {
// 	char c = 'a';

// 	ft_printf("%c", ft_lower(c));

// 	return (0);
// }

// int main (void)
// {
// 	char c = 'G';

// 	ft_printf("%c", ft_lower(c));

// 	return (0);
// }

// C program to demonstrate
// example of tolower() function.
// #include <ctype.h>
// #include <stdio.h>

// int main()
// {
// 	int j = 0;
// 	char str[] = "GeEks@123\n";
// 	char ch;

// 	while (str[j]) {
// 		ch = str[j];
// 		putchar(ft_lower(ch));
// 		j++;
// 	}

// 	return 0;
// }

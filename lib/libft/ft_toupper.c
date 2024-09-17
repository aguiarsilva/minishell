/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:07:47 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/11 14:44:58 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <ctype.h>
** SYNOPSIS: lower case to upper case letter conversion
**
** DESCRIPTION:
** 		The toupper() function converts a lower-case letter to the corresponding
**	upper-case letter.
*/

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z' )
		return (c - 32);
	return (c);
}

// int main (void)
// {
// 	char c = 'a';

// 	ft_printf("%c", ft_toupper(c));

// 	return (0);
// }

// int main (void)
// {
// 	char c = 'G';

// 	ft_printf("%c", ft_toupper(c));

// 	return (0);
// }

// // C program to demonstrate
// // example of toupper() function.
// #include <ctype.h>
// #include <stdio.h>

// int main()
// {
// 	int j = 0;
// 	char str[] = "GeEks@123\n";
// 	char ch;

// 	while (str[j]) {
// 		ch = str[j];
// 		putchar(ft_toupper(ch));
// 		j++;
// 	}

// 	return 0;
// }

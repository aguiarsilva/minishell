/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 15:28:49 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/01 20:14:48 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <stdlib.h>
** SYNOPSIS: convert ASCII string to integer
**
** DESCRIPTION:
** 		The atoi() function converts the initial portion of the string pointed
**	to by str to int representation.
*/

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		nbr;
	int		sign;

	nbr = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nbr = nbr * 10 + *nptr - '0';
		nptr++;
	}
	return (sign * nbr);
}

// int	main(void)
// {
// 	int		val;
// 	char	str[20];

// 	strcpy(str, " +-2147483647");
// 	val = atoi(str);
// 	ft_printf("orig: |String value = %s, Int value = %d\n", str, val);

// 	strcpy(str, " --2147483647");
// 	val = atoi(str);
// 	ft_printf("orig: |String value = %s, Int value = %d\n", str, val);

// 	strcpy(str, " 123 ");
// 	val = atoi(str);
// 	ft_printf("orig: |String value = %s, Int value = %d\n", str, val);

// 	strcpy(str, "cats are awesome");
// 	val = atoi(str);
// 	ft_printf("orig: |String value = %s, Int value = %d\n", str, val);

// 	strcpy(str, " +-2147483647");
// 	val = ft_atoi(str);
// 	ft_printf("my: |String value = %s, Int value = %d\n", str, val);

// 	strcpy(str, " --2147483647");
// 	val = ft_atoi(str);
// 	ft_printf("my: |String value = %s, Int value = %d\n", str, val);

// 	strcpy(str, " 123 ");
// 	val = ft_atoi(str);
// 	ft_printf("my: |String value = %s, Int value = %d\n", str, val);

// 	strcpy(str, "cats are awesome");
// 	val = ft_atoi(str);
// 	ft_printf("my: |String value = %s, Int value = %d\n", str, val);

// 	return (0);
// }
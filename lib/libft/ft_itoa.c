/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:06:13 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/20 14:22:12 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: convert integer to ASCII string
**
** DESCRIPTION:
** 		Allocates (with malloc(3)) and returns a string representing the
**	integer received as an argument. Negative numbers must be handled.
*/

#include "libft.h"

static int	nbr_len(int n)
{
	int	counter_nbr;

	counter_nbr = 0;
	while (n != 0)
	{
		n = n / 10;
		counter_nbr++;
	}
	return (counter_nbr);
}

static char	*convert_to_char(char *nbr, int size, int n, int int_len)
{
	int	temp;

	while (int_len > 0)
	{
		if (n > 9)
		{
			temp = n;
			temp = temp % 10;
			nbr[size -2] = temp + '0';
		}
		else
			nbr[size -2] = n + '0';
		size--;
		int_len--;
		n = n / 10;
	}
	return (nbr);
}

static char	*char_alloc(int n, int int_len)
{
	int		size;
	int		positive_offset;
	int		negativ_offset;
	char	*nbr;

	positive_offset = 1;
	negativ_offset = 2;
	if (n < 0)
		size = int_len + negativ_offset;
	else
		size = int_len + positive_offset;
	nbr = malloc(sizeof(char) * (size));
	if (!nbr)
		return (0);
	nbr[size - 1] = '\0';
	if (n < 0)
	{
		nbr[0] = '-';
		n *= -1;
	}
	nbr = convert_to_char(nbr, size, n, int_len);
	return (nbr);
}

char	*ft_itoa(int n)
{
	char	*nbr;
	int		int_len;

	int_len = nbr_len(n);
	if (n == 0)
	{
		return (ft_strdup("0"));
	}
	else if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nbr = char_alloc(n, int_len);
	return (nbr);
}

// int	main(void)
// {
// 	int n = 51;

// 	char *nbr = ft_itoa(n);
// 	ft_printf("%s", nbr);
// 	free(nbr);
// 	return (0);
// }

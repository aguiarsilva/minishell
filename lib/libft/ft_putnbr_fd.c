/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:49:17 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/20 14:37:39 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: output integer to given file
**
** DESCRIPTION:
** 		Outputs the integer ’n’ to the given file descriptor.
*/

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	single_digit;
	int		first_digit;

	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putstr_fd("2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		first_digit = n % 10;
		ft_putchar_fd(first_digit + 48, fd);
	}
	else
	{
		single_digit = n + 48;
		ft_putchar_fd(single_digit, fd);
	}
}

// int	main(void)
// {
// 	ft_putnbr_fd(-2147483648LL, 2);
// 	return (0);
// }

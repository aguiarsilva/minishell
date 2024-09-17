/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:12:14 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/30 13:57:31 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write (1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	strlen;

	if (s == 0)
	{
		return (ft_putstr("(null)"));
	}
	strlen = 0;
	while (*s != 0)
	{
		ft_putchar(*s);
		s++;
		strlen++;
	}
	return (strlen);
}

int	ft_putnbr_base(long int n, const char *base, int nbr_base, int len)
{
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		len++;
	}
	if (n >= nbr_base)
	{
		len = ft_putnbr_base(n / nbr_base, base, nbr_base, len + 1);
	}
	else
		len++;
	write(1, &base[n % nbr_base], 1);
	return (len);
}

int	ft_putnbr_uns(long unsigned int n, const char *base, int nbr_base, int len)
{
	if (n >= (long unsigned int) nbr_base)
	{
		len = ft_putnbr_base(n / nbr_base, base, nbr_base, len + 1);
	}
	else
		len++;
	write(1, &base[n % nbr_base], 1);
	return (len);
}

int	ft_print_pointer(void *ptr)
{
	int	prefix_offset;

	prefix_offset = 2;
	ft_putstr("0x");
	return (ft_putnbr_uns((long unsigned int) ptr, "0123456789abcdef", 16,
			0 + prefix_offset));
}

// int    main(void)
// {
//     long int decimal_num = -255;
//     long int hex_num = 1234567890;
//     const char *decimal_base = "0123456789";
//     const char *hex_base = "0123456789abcdef";

//     ft_printf("Decimal number: %ld\n", decimal_num);
// 	ft_printf("Decimal base representation: ");
//     int len_dec = ft_putnbr_base(decimal_num, decimal_base, 10, 0);

//     ft_printf("len dec = %d\n", len_dec);

//     ft_printf("Hexadecimal number: %ld\n", hex_num);
// 	ft_printf("Hexadecimal base representation: ");
//     int len_hex = ft_putnbr_base(hex_num, hex_base, 16, 0);
//     ft_printf("len hex = %d\n", len_hex);

//     return 0;
// }

// int	main(void)
// {
// 	ft_putstr(NULL);
// 	// ft_printf("%s", NULL);
// }

// int main(void)
// {
//     int x = 42;
//     void *ptr = &x;
//     ft_print_pointer(ptr);
//     // ft_printf("\n");
//     // ft_printf("%d", ft_printf("%p", ptr));
//     return 0;
// }
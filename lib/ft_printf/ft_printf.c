/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:57:07 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/30 14:00:08 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	flag_check(const char format, va_list args)
{
	if (format == 'd' || format == 'i')
		return (ft_putnbr_base(va_arg(args, int), "0123456789", 10, 0));
	if (format == 'u')
		return (ft_putnbr_base(va_arg(args, unsigned int),
				"0123456789", 10, 0));
	if (format == 'x')
		return (ft_putnbr_base(va_arg(args, unsigned int),
				"0123456789abcdef", 16, 0));
	if (format == 'X')
		return (ft_putnbr_base(va_arg(args, unsigned int),
				"0123456789ABCDEF", 16, 0));
	if (format == 'c')
		return (ft_putchar((char)va_arg(args, int)));
	if (format == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (format == '%')
		return (ft_putchar('%'));
	if (format == 'p')
		return (ft_print_pointer(va_arg(args, void *)));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg_ptr;
	int		current_index;
	int		c_printed;

	current_index = 0;
	c_printed = 0;
	va_start(arg_ptr, format);
	while (format[current_index])
	{
		if (format[current_index] == '%'
			&& ft_strchr_duplicate("cspdiuxX%", format[current_index + 1]) != 0)
		{
			c_printed += flag_check(format[current_index + 1], arg_ptr);
			current_index++;
		}
		else
			c_printed += ft_putchar(format[current_index]);
		current_index++;
	}
	va_end(arg_ptr);
	return (c_printed);
}

// int	main(void)
// {
// 	// int		age = 30;
// 	// char	name[] = "John Smith";
//
// 	ft_printf("Hello there! I like the numbers %d, %d, and %d", 1, 3, 7);
// 	return (0);
// }

// int	main(void)
// {
// 	ft_printf("my| %x \n", 1234567890);
// 	ft_printf("ori| %x ", 1234567890);
// }
//	 int main(void)
//	 {
//	 	ft_printf(" %p %p ", 0, 0);
//	 	ft_printf(" %p %p ", 0, 0);
//	 }
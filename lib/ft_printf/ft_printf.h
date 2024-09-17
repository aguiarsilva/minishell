/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:43:08 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/30 14:13:37 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h> 
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>

// main function

int		ft_printf(const char *s, ...);

// helper function
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_putnbr_base(long int n, const char *base, int nbr_base, int len);
int		ft_putnbr_uns(long unsigned int n, const char *base,
			int nbr_base, int len);
int		ft_print_pointer(void *ptr);

#endif
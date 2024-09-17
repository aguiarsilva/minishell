/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 19:54:44 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/02/17 19:54:44 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_words(char const *s, char c)
{
	size_t	cursor_index;
	size_t	word_counter;

	cursor_index = 0;
	word_counter = 0;
	while (s != 0 && s[cursor_index] != '\0')
	{
		if (s[cursor_index] == c)
			cursor_index++;
		else
		{
			word_counter++;
			while (s[cursor_index] != c && s[cursor_index] != '\0')
				cursor_index++;
		}
	}
	return (word_counter);
}

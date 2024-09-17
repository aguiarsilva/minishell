/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:15:41 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/20 15:22:42 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: concatenate two strings into a new string (with malloc)
**
** DESCRIPTION:
** 		Allocates (with malloc(3)) and returns a new string, which is the
**	result of the concatenation of ’s1’ and ’s2’.
*/

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*joined_str;
	size_t	end_joined_len;

	if (!s1 || !s2)
		return (0);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	joined_str = malloc(sizeof(char) * (total_len + 1));
	if (!joined_str)
	{
		return (0);
	}
	ft_strlcpy(joined_str, s1, ft_strlen(s1)+1);
	end_joined_len = ft_strlen(joined_str);
	ft_strlcat(joined_str + end_joined_len, s2, ft_strlen(s2)+1);
	return (joined_str);
}

// int	main(void)
// {
// 	char *str1 = "I am in love ";
// 	char *str2 = "with cats";

// 	ft_printf("The new String is: %s", ft_strjoin(str1, str2));
// }
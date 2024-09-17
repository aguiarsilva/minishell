/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:21:20 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/20 14:26:50 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: delete element from list
**
** DESCRIPTION:
** 		Takes as a parameter an element and frees the memory of the element’s
**	content using the function ’del’ given as a parameter and free the element.
**	The memory of ’next’ must not be freed.
*/

#include "libft.h"

void	ft_lstdelone(t_list	*lst, void (*del)(void*))
{
	if (lst)
	{
		del(lst->content);
		free(lst);
	}
}

// int main()
// {
// 	t_list	*lst;
// 	t_list	*second_element;
// 	char	*str = "Hello";

// 	str = strdup("Hello");
// 	lst = (t_list *)malloc(sizeof(t_list));
// 	lst->content = str;
// 	lst->next = NULL;

// 	str = strdup("World");
// 	second_element = (t_list *)malloc(sizeof(t_list));
// 	second_element->content = str;
// 	second_element->next = NULL;

// 	lst->next = second_element;

// 	ft_lstdelone(lst, free);

// 	return (0);
// }

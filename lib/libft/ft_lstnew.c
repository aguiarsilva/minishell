/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:29:58 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/20 14:31:05 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: create new list
**
** DESCRIPTION:
** 		Allocates (with malloc(3)) and returns a new element. The variable
**	’content’ is initialized with the value of the parameter ’content’. The
**	variable ’next’ is initialized to NULL.
*/

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

// int	main(void)
// {
// 	int		*a;
// 	t_list	*new_node;

// 	a = malloc(sizeof(int));
// 	*a = 5;
// 	new_node = ft_lstnew(a);
// 	if (new_node)
// 	{
// 		ft_printf("New node created with content: %d\n",
// 		*(int *)new_node->content);
// 		free(new_node);
// 	}
// 	else
// 		ft_printf("Error creating new node\n");
// 	return (0);
// }

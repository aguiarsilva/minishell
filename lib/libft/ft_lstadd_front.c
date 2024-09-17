/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:21:27 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/20 14:23:36 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: add new element at beginning of list
**
** DESCRIPTION:
** 		Adds the element ’new’ at the beginning of the list.
*/

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

/*new->next = *lst 	sets the next pointer from
new list to the previous list 
*/
//*lst = new			set's the pointer from the previous list to the new one

// int	main(void)
// {
// 	t_list	*new;
// 	t_list	*current;
// 	int		i;

// 	new = ft_lstnew("new node");
// 	current = new;
// 	i = 0;

// 	while (i < 5)
// 	{
// 		t_list *new_node = ft_lstnew("node x");
// 		ft_lstadd_front(&current, new_node);
// 		i++;
// 	}

// 	ft_printf("List after adding new node at the front: ");
// 	return (0);
// }

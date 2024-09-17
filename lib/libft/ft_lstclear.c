/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:44:49 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/20 14:57:44 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: delete sequence of elements of list from a starting point
**
** DESCRIPTION:
** 		Deletes and frees the given element and every successor of that element,
**	using the function ’del’ and free(3). Finally, the pointer to the list must
**	be set to NULL.
*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*to_del;

	current = *lst;
	while (current)
	{
		to_del = current;
		del(to_del->content);
		current = current->next;
		free(to_del);
	}
	*lst = NULL;
}

// int	main()
// {
// 	t_list *lst;
// 	char *str1 = "Hello";
// 	char *str2 = "World";

// 	str1 = strdup("Hello");
// 	lst = ft_lstnew(str1);
// 	str2 = strdup("World");
// 	ft_lstadd_back(&lst, ft_lstnew(str2));
// 	ft_lstclear(&lst, free);
// 	if (lst == NULL)
// 	{
// 		ft_printf("List is now empty\n");
// 	}
// 	return (0);
// }

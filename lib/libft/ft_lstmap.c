/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:45:22 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/20 14:29:56 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: apply function to content of all list's elements into new list
**
** DESCRIPTION:
** 		Iterates the list ’lst’ and applies the function ’f’ to the content of
**	each element. Creates a new list resulting of the successive applications of
**	the function ’f’. The ’del’ function is used to delete the content of an
**	element if needed.
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*applied_f_lst;
	t_list	*start_of_applied_f_lst;

	if (lst == NULL || f == NULL)
		return (NULL);
	start_of_applied_f_lst = 0;
	while (lst)
	{
		applied_f_lst = ft_lstnew((*f)(lst->content));
		if (applied_f_lst == NULL)
		{
			ft_lstclear(&start_of_applied_f_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&start_of_applied_f_lst, applied_f_lst);
		lst = lst->next;
	}
	return (start_of_applied_f_lst);
}

// int main ()
// {
// 	t_list *list;
// 	list = NULL;
// 	list = ft_lstadd_front(list, "Päckchen 1");
// 	list = ft_lstadd_front(list, "Päckchen 2");
// 	list = ft_lstadd_front(list, "Päckchen 3");

// 	print_list(list);

// 	return 0;
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:30:02 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/01/20 15:11:07 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <stdlib.h>
** SYNOPSIS: memory allocation
**
** DESCRIPTION:
** 		The calloc() function contiguously allocates enough space for count
**	objects that are size bytes of memory each and returns a pointer to the
**	allocated memory. The allocated memory is filled with bytes of value
**	zero.
*/

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void		*ptr;
	size_t		tot_size;

	tot_size = count * size;
	ptr = malloc(tot_size);
	if (!ptr)
	{
		return (0);
	}
	ft_bzero(ptr, tot_size);
	return (ptr);
}

// int main(void) {
//   //default_case
//   // Specify number of elements in array
// 	int num_elements = 10;

// 	int i = 0;

//   // Allocate memory for array using calloc
// 	int *array = (int *) ft_calloc(num_elements, sizeof(int));
// 	if (array == NULL) {
// 	fprintf(stderr, "Error allocating memory with calloc\n");
// 	return 1;
//   }

//   // Initialize array elements to 0 (calloc initializes all elements to 0)
// 	while(i < num_elements)
//   {
// 	ft_printf("%d ", array[i]);
// 	i++;
//   }
// 	ft_printf("\n");

// 	// Free memory when done
// 	free(array);
// 	// check if void pointer is returned
// 	void	*str = ft_calloc(0,0);

// 	if (!str)
// 		ft_printf("You returned a NULL Pointer");
// 	else
// 		ft_printf("it should be a void pointer, so that's correct :) ");

// 	free(str);
// 	return (0);
// }

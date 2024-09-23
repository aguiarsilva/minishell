
#include "lib/minishell.h"

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("malloc failed");
		return (NULL);
	}
	ft_memset(ptr, 0, size);
	return (ptr);
}

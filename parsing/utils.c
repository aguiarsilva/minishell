#include "../lib/minishell.h"

char    *ft_strncpy(char *dest, const char *src, int n)
{
    int  i;

    i = -1;
    while (++i < n && src[i])
        dest[i] = src[i];
    dest[i] = '\0';
    return (dest);
}

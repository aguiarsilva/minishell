

#include "../lib/minishell.h"

bool	is_valid_identifier(const char *key, bool check_first_char)
{
	int	i;

	i = 0;

	if (key == NULL || *key == '\0')
		return (false);
	// If first character needs special validation
	if (check_first_char && (!ft_isalpha(key[0]) && key[0] != '_'))
		return (false);
	// Check all characters (starting from the second if first is validated)
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	len;
	size_t	copy_len;
	char	*dest;

	len = ft_strlen(s1);
	if (len < n)
		copy_len = len;
	else
		copy_len = n;
	dest = malloc(copy_len + 1);
	if (dest == NULL)
		return (NULL);
	ft_memcpy(dest, s1, copy_len);
	dest[copy_len] = '\0';
	return (dest);
}
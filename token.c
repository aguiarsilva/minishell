#include "../lib/minishell.h"

char	*ft_strtotoken(char *str, const char *delim)
{
	static char	*last_tk;
	char		*cur_tk_end;

	if (str == NULL)
		str = last_tk;
	if (str == NULL)
		return (NULL);
	str += ft_strspn(str, delim);
	if (*str == '\0')
		return (NULL);
	cur_tk_end = quoted_str(str, delim);
	if (*cur_tk_end == '\0')
		last_tk = NULL;
	else
	{
		*cur_tk_end = '\0';
		last_tk = cur_tk_end + 1;
	}
	return (str);
}

size_t	ft_strspn(const char *str, const char *accept)
{
	const char	*s;
	const char	*a;
	bool		found;

	s = str;
	while (*s)
	{
		a = accept;
		found = false;
		while (*a)
		{
			if (*s == *a)
			{
				found = true;
				break ;
			}
			a++;
		}
		if (!found)
			break ;
		s++;
	}
	return (s - str);
}

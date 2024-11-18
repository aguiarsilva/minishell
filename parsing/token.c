#include "../lib/minishell.h"

char	*ft_strtok(char *str, const char *delim)
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

char	*quoted_str(char *str, const char *delim)
{
	char	*tk_end;
	bool	in_quote;
	char	ch_quote;

	tk_end = str;
	in_quote = false;
	ch_quote = '\0';
	while (*tk_end)
	{
		if (is_quote(*tk_end))
		{
			if (in_quote && *tk_end == ch_quote)
				in_quote = false;
			else if (!in_quote)
			{
				in_quote = true;
				ch_quote = *tk_end;
			}
		}
		else if (!in_quote && ft_strchr_duplicate(delim, *tk_end))
			break ;
		tk_end++;
	}
	return (tk_end);
}

//void	remove_quotes(char **str)
//{
//	char	*src;
//	char	*dest;
//	char	begin_quote;
//
//	src = *str;
//	dest = *str;
//	begin_quote = '\0';
//	if (*src == '"' || *src == '\'')
//	{
//		begin_quote = *src;
//		src++;
//	}
//	while (*src)
//	{
//		if (begin_quote == '\0' && (*src == '"' || *src == '\''))
//		{
//			src++;
//			continue ;
//		}
//		*dest++ = *src++;
//	}
//	if (begin_quote != '\0' && dest > *str && (*dest - 1) == begin_quote)
//		dest--;
//	*dest = '\0';
//}

//char	*ft_strtok_rm_quotes(char *str, const char *delim)
//{
//	static char		*last_tk;
//	char			*cur_tk_end;
//
//	if (str == NULL)
//		str = last_tk;
//	if (str == NULL)
//		return (NULL);
//	str += ft_strspn(str, delim);
//	if (*str == '\0')
//		return (NULL);
//	cur_tk_end = quoted_str(str, delim);
//	if (*cur_tk_end == '\0')
//		last_tk = NULL;
//	else
//	{
//		*cur_tk_end = '\0';
//		last_tk = cur_tk_end + 1;
//	}
//	remove_quotes(&str);
//	return (str);
//}

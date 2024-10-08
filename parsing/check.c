#include "../lib/minishell.h"

bool	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

bool	is_redirection_symbol(char c)
{
	return (c == '<' || c == '>');
}

bool	is_redir_operator(const char *wd)
{
	return (ft_strcmp(wd, ">") == 0 || ft_strcmp(wd, "<") == 0
		|| ft_strcmp(wd, "<<") == 0 || ft_strcmp(wd, ">>") == 0);
}

char	*verify_syntax(char *str)
{
	char	*new;
	size_t	len;

	len = ft_strlen(str);
	if (!str || (len < 2))
		return (NULL);
	new = (char *)malloc(len - 1);
	if (!new)
		return (NULL);
	ft_strncpy(new, str + 1, len - 2);
	new[len - 2] = '\0';
	return (ft_strdup(new));
}

int	str_spaces(const char *str)
{
	while (*str)
	{
		if (*str != 32)
			return (0);
		str++;
	}
	return (1);
}

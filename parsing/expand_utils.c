

#include "../lib/minishell.h"

char	*get_exit_code_value(t_env *env_lst)
{
	while (env_lst)
	{
		if (ft_strncmp("EC", env_lst->key, 2) == 0
			&& ft_strlen(env_lst->key) == 2)
			return (env_lst->value);
		env_lst = env_lst->next;
	}
	return (NULL);
}

char	*append_remainder(char *base, char *remainder)
{
	char	*result;

	if (!remainder[0])
		return (base);
	result = ft_strjoin(base, remainder);
	free(base);
	return (result);
}

bool	is_valid_env_char(char next_char)
{
	if (next_char == '\0' || ft_isspace(next_char)
		||next_char == '"' || next_char == '\''
		||next_char == '}' || next_char == ')'
		||next_char == ':' || next_char == '='
		||next_char == '^' || next_char == '%'
		|| (next_char >= '+' && next_char <= '/'))
		return (false);
	return (true);
}

bool	is_var_delimiter(char c)
{
	if (c == '"' || c == '\'' || c == '}' || c == ')'
		|| c == '$' || ft_isspace(c))
		return (false);
	return (true);
}

int	calculate_brace_offset(char *split, int start, int *i)
{
	int	offset;

	offset = 0;
	if ((split[start] == '{' && split[*i] == '}')
		|| (split[start] == '(' && split[*i] == ')'))
	{
		offset++;
		(*i)++;
	}
	if (split[start + 1] == '{')
	{
		offset = -1;
		ft_putstr_fd("Error: Bad syntax near '{'\n", 2);
	}
	return (offset);
}

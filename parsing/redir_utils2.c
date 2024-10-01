
#include "../lib/minishell.h"

int	check_no_space_redir_excl_special(char *input)
{
	int	no_space;
	int	i;

	no_space = 0;
	i = -1;
	while (input[++i])
	{
		skip_quotes_without_copy(input, &i);
		if (i > 0 && (input[i] == '<' || input[i] == '>' || input[i] == '|')
			&& input[i - 1] != 26)
		{
			no_space++;
			if ((input[i] == '<' && input [i + 1] == '>')
				|| (input[i] == '>' && input[i + 1] == '<')
				|| (input[i - 1] == '<' || input [i - 1] == '>'))
				no_space--;
		}
	}
	return (no_space);
}

void	copy_and_skip_quotes(char *str, int *i, char **input, int *j)
{
	char	temp;

	temp = '\0';
	if (str[*i] == '"' || str[*i] == '\'')
	{
		temp = str[*i];
		(*input)[(*j)++] = str[*i];
		(*i)++;
		while (str[*i] && str[*i] != temp)
		{
			(*input)[(*j)++] = str[*i];
			(*i)++;
		}
	}
}

void	skip_quotes_without_copy(char *str, int *i)
{
	char	temp;

	temp = '\0';
	if (str[*i] == '"' || str[*i] == '\'')
	{
		temp = str[*i];
		(*i)++;
		while (str[*i] && str[*i] != temp)
			(*i)++;
	}
}

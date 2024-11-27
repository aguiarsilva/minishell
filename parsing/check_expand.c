

#include "../lib/minishell.h"

static int	process_dollar_sign(char *str_to_expand, int *i,
								char **exp_word, t_env *env_lst)
{
	if (is_valid_env_char(str_to_expand[*i + 1]))
	{
		(*i)++;
		if (expand_to_str(str_to_expand, i, exp_word, env_lst))
			return (1);
		(*i)--;
	}
	else
	{
		*exp_word = ft_charjoin_mod(*exp_word, str_to_expand[*i]);
		if (!(*exp_word))
			return (1);
	}
	return (0);
}

char	*expand_word(char *word, int i, t_env *env_lst)
{
	char	*exp_word;

	exp_word = ft_calloc(1, 1);
	if (!exp_word)
		return (NULL);
	while (word[++i])
	{
		if (word[0] != '\'' && word[i] == '$')
		{
			if (process_dollar_sign(word, &i, &exp_word, env_lst))
				return (NULL);
		}
		else
		{
			exp_word = ft_charjoin_mod(exp_word, word[i]);
			if (!exp_word)
				return (NULL);
		}
		if (!word[i])
			break ;
	}
	return (exp_word);
}

char	*create_fake_pid(int *i)
{
	char	*exp_var;

	(*i)++;
	exp_var = ft_itoa(42424);
	if (!exp_var)
		return (NULL);
	return (exp_var);
}

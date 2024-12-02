/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:59:03 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/11/30 16:19:51 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static int	process_dollar_sign(char *str_to_expand, int *i,
								char **exp_word, t_env *env_lst)
{
	char	*temp;

	if (is_valid_env_char(str_to_expand[*i + 1]))
	{
		(*i)++;
		if (expand_to_str(str_to_expand, i, exp_word, env_lst))
			return (1);
		(*i)--;
	}
	else
	{
		temp = ft_charjoin_mod(*exp_word, str_to_expand[*i]);
		if (!temp)
			return (1);
		if (!(str_to_expand[*i] == '$' &&
		(str_to_expand[*i + 1] == '\0' || str_to_expand[*i + 1] == ' ')))
			free(*exp_word);
		*exp_word = temp;
	}
	return (0);
}

static char	*handle_regular_character(char *exp_word, char current_char)
{
	char	*temp;

	temp = ft_charjoin_mod(exp_word, current_char);
	if (!temp)
	{
		free(exp_word);
		return (NULL);
	}
	// free(exp_word);
	return (temp);
}

static bool	should_expand_variable(char *word, int index)
{
	return (word[0] != '\'' && word[index] == '$');
}

char	*expand_word(char *word, int i, t_env *env_lst)
{
	char	*exp_word;

	exp_word = ft_calloc(1, 1);
	if (!exp_word)
		return (NULL);
	while (word[++i])
	{
		if (should_expand_variable(word, i))
		{
			if (process_dollar_sign(word, &i, &exp_word, env_lst))
			{
				free(exp_word);
				return (NULL);
			}
		}
		else
		{
			exp_word = handle_regular_character(exp_word, word[i]);
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

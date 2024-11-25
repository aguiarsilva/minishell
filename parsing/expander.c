

#include "../lib/minishell.h"

static char	*find_exit_code(char *temp, t_env *env_lst)
{
	char	*exit_code_value;
	char	*result;

	if (!temp || !env_lst)
		return (NULL);
	exit_code_value = get_exit_code_value(env_lst);
	if (!exit_code_value)
		return (NULL);
	result = ft_strdup(exit_code_value);
	if (!result)
		return (NULL);
	result = append_remainder(result, &temp[1]);
	return (result);
}

static int	find_exp_var_in_env(char *temp, char **exp_var, t_env *env_lst)
{
	char	*temp2;
	char	*temp3;
	int		i;

	temp2 = ft_calloc(1, 1);
	*exp_var = NULL;
	i = -1;
	while (temp[++i])
	{
		temp2 = ft_charjoin_mod(temp2, temp[i]);
		if (!temp2)
			return (1);
		temp3 = get_key_in_env_lst(env_lst, temp2);
		if (temp3)
			break ;
	}
	free(temp2);
	if (temp3 && !(ft_isalnum(temp[i + 1])) && temp[i + 1] != '_')
	{
		*exp_var = ft_strjoin(temp3, &temp[i + 1]);
		free(temp3);
		if (!(*exp_var))
			return (1);
	}
	return (0);
}

static int	determine_exp_var(char *temp, t_env *lst, char **exp_var)
{
	if (ft_isdigit(temp[0]))
	{
		*exp_var = ft_strdup(temp + 1);
		if (!(*exp_var))
			return (1);
	}
	else if (temp[0] == '?')
	{
		*exp_var = find_exit_code(temp, lst);
		if (!(*exp_var))
			return (1);
	}
	else
		if (find_exp_var_in_env(temp, exp_var, lst))
			return (1);
	return (0);
}

static int	extract_and_expand_var(char *split, int *i,
			t_env *env_lst, char **exp_var)
{
	int		start;
	int		offset;
	int		var_length;
	char	*var_name;

	start = *i;
	while (split[*i] && is_var_delimiter(split[*i]))
		(*i)++;
	offset = calculate_brace_offset(split, start, i);
	if (offset == -1)
		return (1);
	var_length = *i - start - (2 * offset);
	var_name = ft_substr(split, start + offset, var_length);
	if (!var_name)
		return (1);
	if (determine_exp_var(var_name, env_lst, exp_var))
	{
		free(var_name);
		return (1);
	}
	free(var_name);
	return (0);
}

int	expand_to_str(char *str_to_expand, int *i, char **exp_word, t_env *env_lst)
{
	char	*exp_var;

	exp_var = NULL;
	if (str_to_expand[*i] && str_to_expand[*i] == '$') // edge case $$ returns process ID but we are not allowed to use get pid to get a real number
	{
		exp_var = create_fake_pid(i);
		if (!exp_var)
			return (free(*exp_word), 1);
	}
	else
	{
		if (extract_and_expand_var(str_to_expand, i, env_lst, &exp_var))
			return (free(*exp_word), 1);
	}
	if (exp_var)
	{
		*exp_word = ft_strjoin(*exp_word, exp_var);
		if (!(*exp_word))
			return (1);
	}
	free(exp_var);
	return (0);
}


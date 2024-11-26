/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:51:13 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/11/26 10:23:27 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static bool	parse_export_arg(const char *arg, char **key_out,
			char **value_out)
{
	char	*sign;
	size_t	key_len;

	if (arg == NULL || *arg == '\0')
		return (false);
	sign = ft_strchr_duplicate(arg, '=');
	if (sign)
	{
		if (ft_strchr_duplicate(sign + 1, '='))
		{
			printf("Error: Invalid argument: '%s' (too many '=' signs)\n", arg);
			return (false);
		}
		key_len = (size_t)(sign - arg);
		*key_out = ft_strndup(arg, key_len);
		*value_out = ft_strdup(sign + 1);
	}
	else
	{
		*key_out = ft_strdup(arg);
		*value_out = ft_strdup("");
	}
	return (true);
}

static bool	check_export_argument(char *arg, char **key_out, char **value_out)
{
	if (!parse_export_arg(arg, key_out, value_out))
		return (false);
	if (!is_valid_identifier(*key_out, true))
	{
		printf("Error: '%s' is not a valid identifier for export.\n", *key_out);
		free(*key_out);
		free(*value_out);
		return (false);
	}
	printf("DEBUG Valid export argument.\n");
	printf("DEBUG Key: %s\n", *key_out);
	printf("DEBUG Value: %s\n", *value_out && **value_out ? *value_out : "(empty)");
	return (true);
}

static bool	is_valid_export_format(char **args, int arg_count)
{
	int		i;
	char	*equals;

	i = 0;
	while (i < arg_count)
	{
		if (ft_strcmp(args[i], "=") == 0)
		{
			return (false);
		}
		equals = ft_strchr_duplicate(args[i], '=');
		if (equals && i + 1 < arg_count)
		{
			if (args[i + 1][0] == '=' || equals[1] == '\0')
				return (false);
		}
		i++;
	}
	return (true);
}

static void	process_arguments(char **args, int arg_count, t_env **env_list)
{
	char	*key;
	char	*value;
	int		i;

	key = NULL;
	value = NULL;
	i = 0;
	while (i < arg_count)
	{
		if (check_export_argument(args[i], &key, &value) == true)
		{
			add_or_update_env_var(env_list, key, value);
			free(key);
			free(value);
		}
		i++;
	}
}

int	export_builtin(char **args, t_env **env_list)
{
	int		i;
	int		arg_count;
	char	*key;
	char	*value;

	i = 0;
	key = NULL;
	value = NULL;
	if (args == NULL)
		return (1);
	count_arg_from_args(args);
	if (handle_no_arguments(env_list, arg_count))
		return (0);
	if (!is_valid_export_format(args, arg_count))
		return (1);
	process_arguments(args, arg_count, env_list);
	return (0);
}

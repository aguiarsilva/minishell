/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:16:01 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/11/26 12:34:53 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static size_t	count_env_nodes(t_env *env_list)
{
	size_t		env_count;
	t_env		*current;

	env_count = 0;
	current = env_list;
	while (current != NULL)
	{
		env_count++;
		current = current->next;
	}
	return (env_count);
}

char	**env_list_to_array(t_env *env_list)
{
	size_t		env_count;
	size_t		key_len;
	size_t		value_len;
	char		**env_array;
	int			i;

	env_count = count_env_nodes(env_list);
	env_array = (char **)malloc(sizeof(char *) * (env_count + 1));
	i = 0;
	while (env_list != NULL)
	{
		key_len = strlen(env_list->key);
		value_len = strlen(env_list->value);
		env_array[i] = malloc(key_len + value_len + 2);
		ft_strcpy(env_array[i], env_list->key);
		env_array[i][key_len] = '=';
		ft_strcpy(env_array[i] + key_len + 1, env_list->value);
		i++;
		env_list = env_list->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

char	*get_key_in_env_lst(t_env *env_lst, char *key)
{
	char	*value;

	value = NULL;
	while (env_lst)
	{
		if (ft_strncmp(env_lst->key, key, ft_strlen(env_lst->key)) == 0)
		{
			value = ft_strdup(env_lst->value);
			if (!value)
				return (NULL);
		}
		env_lst = env_lst->next;
	}
	return (value);
}

int	set_value_in_env_lst(t_env *env_lst, char *key, char *value)
{
	while (env_lst)
	{
		if (ft_strncmp(env_lst->key, key, ft_strlen(env_lst->key)) == 0)
		{
			if (*env_lst->value != '\0')
				free(env_lst->value);
			if (!value)
				env_lst->value = ft_strdup("\0");
			else
				env_lst->value = ft_strdup(value);
			if (!env_lst->value)
				return (1);
		}
		env_lst = env_lst->next;
	}
	return (0);
}

void	update_exit_code(t_env *env_lst, int exit_code)
{
	t_env	*ec_node;

	if (!env_lst)
		return ;
	ec_node = env_lst;
	while (ec_node)
	{
		if (ft_strcmp(ec_node->key, "EC") == 0)
		{
			free(ec_node->value);
			ec_node->value = ft_itoa(exit_code);
			break ;
		}
		ec_node = ec_node->next;
	}
}

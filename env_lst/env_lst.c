/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:16:01 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/11/26 12:34:36 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static t_env	*create_env_node(char *key, char *value)
{
	t_env	*node;
	int		shell_level;

	node = (t_env *)malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	ft_bzero(node, sizeof(*node));
	node->key = ft_strdup(key);
	if (ft_strncmp(node->key, "SHLVL", ft_strlen(node->key)) == 0)
	{
		shell_level = ft_atoi(value);
		shell_level += 1;
		node->value = ft_itoa(shell_level);
	}
	else if (ft_strncmp(node->key, "EC", ft_strlen(node->key)) == 0)
		node->value = ft_strdup("0");
	else
	{
		if (value == NULL)
			node->value = ft_strdup("");
		else
			node->value = ft_strdup(value);
	}
	node->next = NULL;
	return (node);
}

static void	split_env_variable(char *env_var, char **key, char **value)
{
	char	*delimiter;
	int		offset;

	delimiter = ft_strchr_duplicate(env_var, '=');
	offset = delimiter - env_var;
	*key = ft_substr(env_var, 0, offset);
	*value = ft_substr(delimiter + 1, 0, ft_strlen(env_var) - (offset));
}

static void	env_lst_addback(t_env **lst, t_env *new)
{
	t_env	**current;
	char	*current_key;
	char	*current_value;

	current = lst;
	while (*current)
	{
		current_key = (*current)->key;
		if (ft_strncmp(current_key, new->key, ft_strlen(new->key)) == 0 \
		&& ft_strlen(new->key) == ft_strlen(current_key))
		{
			current_value = (*current)->value;
			if (current_value)
				free(current_value);
			if (new->value == NULL)
				(*current)->value = ft_strdup("");
			else
				(*current)->value = ft_strdup(new->value);
			free_env_node(new);
			return ;
		}
		current = &(*current)->next;
	}
	*current = new;
}

static t_env	*initialize_base_env(char **argv)
{
	t_env	*lst;
	t_env	*tmp;

	lst = create_env_node("PWD", getcwd(NULL, 0));
	tmp = create_env_node("SHLVL", "0");
	env_lst_addback(&lst, tmp);
	tmp = create_env_node("_", argv[0]);
	env_lst_addback(&lst, tmp);
	return (lst);
}

t_env	*create_env_lst(char **ori_env, char **argv)
{
	t_env	*env_lst;
	t_env	*new_node;
	char	*key;
	char	*value;
	int		i;

	env_lst = NULL;
	i = 0;
	if (ori_env == NULL)
		return (initialize_base_env(argv));
	while (ori_env[i])
	{
		split_env_variable(ori_env[i], &key, &value);
		new_node = create_env_node(key, value);
		env_lst_addback(&env_lst, new_node);
		free(key);
		free(value);
		i++;
	}
	new_node = create_env_node("EC", NULL);
	env_lst_addback(&env_lst, new_node);
	return (env_lst);
}

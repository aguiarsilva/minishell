
#include "../lib/minishell.h"

// Helper function to convert t_env linked list to char**
char **env_list_to_array(t_env *env_list)
{
	int		env_count;
	t_env	*current;
	size_t	key_len;
	size_t	value_len;

	env_count = 0;
	current = env_list;
	while (current != NULL)
	{
		env_count++;
		current = current->next;
	}

	char **env_array = (char **)malloc(sizeof(char *) * (env_count + 1));

	// Convert the linked list to the array
	current = env_list;
	int i = 0;
	while (current != NULL)
	{
		key_len = strlen(current->key);
		value_len = strlen(current->value);
		env_array[i] = malloc(key_len + value_len + 2);
		ft_strcpy(env_array[i], current->key);
		env_array[i][key_len] = '=';
		ft_strcpy(env_array[i] + key_len + 1, current->value);
		i++;
		current = current->next;
	}
	env_array[i] = NULL;

	return (env_array);
}
t_env	*create_env_node(char *key, char *value)
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

	delimiter = ft_strchr(env_var, '=');
	offset = delimiter - env_var;
	*key = ft_substr(env_var, 0, offset);
	*value = ft_substr(delimiter + 1, 0, ft_strlen(env_var) - (offset));
}

static void	free_env_node(t_env *node)
{
	if (node)
	{
		if (node->key)
			free(node->key);
		if (node->value)
			free(node->value);
		free(node);
	}
}

static void	free_env_list(t_env **env_lst)
{
	t_env	*current;

	while (*env_lst)
	{
		current = *env_lst;
		*env_lst = (*env_lst)->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
	}
}

void	env_lst_addback(t_env **lst, t_env *new)
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

void	print_node(t_env *node) // debug only
{
	t_env	*current;

	current = node;
	while (current)
	{
		printf("Key: %s, Value: %s, EC: %d\n",
			current->key ? current->key : "(null)",
			current->value ? current->value : "(null)",
			current->exit_code);
		current = current->next;
	}
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

t_env	*create_env(char **ori_env, char **argv)
{
	t_env	*dup_env_lst;
	t_env	*new_node;
	char	*key;
	char	*value;
	int		i;

	dup_env_lst = NULL;
	i = 0;
	if (ori_env == NULL)
		return (initialize_base_env(argv));
	while (ori_env[i])
	{
		split_env_variable(ori_env[i], &key, &value);
		new_node = create_env_node(key, value);
		// print_node(new_node);
		env_lst_addback(&dup_env_lst, new_node);
		free(key);
		free(value);
		i++;
	}
	return (dup_env_lst);
}

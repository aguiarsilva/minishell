
#include "lib/minishell.h"

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

// Helper function to convert t_env linked list to char**
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

void	free_env_node(t_env *node)
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

void	free_env_list(t_env **env_lst)
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

// Function to update exit_code in t_env based on key
void	update_env_exit_code(t_env *env_list, const char *key, t_cmd *cmd_lst)
{
	while (env_list != NULL)
	{
		// Check if the current key matches the input key
		if (ft_strcmp(env_list->key, key) == 0)
		{
			env_list->exit_code = cmd_lst->exit_code; // Update the exit_code
			printf("Updated exit_code for key '%s' to %d\n", key, cmd_lst->exit_code);
			return ;
		}
		env_list = env_list->next; // Move to the next node
	}
	// If key is not found, print a message
	fprintf(stderr, "Key '%s' not found in environment list.\n", key);
}

#include "lib/minishell.h"

void add_or_update_env_var(t_env **env_list, char *key, char *value) // i have function which updates an env_var and i have a function which adds a new env_var , maybe use my version
{
	t_env *curr = *env_list;

	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			free(curr->value);
			curr->value = ft_strdup(value);
			return;
		}
		curr = curr->next;
	}
	t_env *new_var = malloc(sizeof(t_env));
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
	new_var->next = *env_list;
	*env_list = new_var;
}

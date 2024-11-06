#include "lib/minishell.h"

t_env *find_env_var(t_env *env_list, char *key)
{
    while (env_list)
    {
        if (ft_strcmp(env_list->key, key) == 0)
            return env_list;
        env_list = env_list->next;
    }
    return NULL;
}

void add_or_update_env_var(t_env **env_list, char *key, char *value)
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

/*void print_env_list(t_env *env_list)
{
    t_env *current = env_list;

    while (current)
    {
        printf("declare -x %s=\"%s\"\n", current->key, current->value);
        current = current->next;
    }
}*/

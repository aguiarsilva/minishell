#include "../lib/minishell.h"

int is_valid_identifier(const char *key)
{
    int i = 0;

    if (!key || (!isalpha(key[0]) && key[0] != '_'))
        return 0;
    while (key[++i])
    {
        if (!isalnum(key[i]) && key[i] != '_')
            return 0;
    }
    return 1;
}

int print_export_error(const char *key)
{
    fprintf(stderr, "export: `%s': not a valid identifier\n", key);
    return 1;
}

int export_builtin(char **args, t_env **env_list)
{
    int exit_code = 0;
    int i = 1;

    if (!args[i])
        print_env_list(*env_list); // List env vars if no arguments
    else
    {
        while (args[i])
        {
            char *key = args[i];
            char *value = ft_strchr(args[i], '=');

            if (value)
            {
                *value = '\0'; // Null-terminate key
                value++;       // Move pointer to start of value
                if (is_valid_identifier(key))
                    add_or_update_env_var(env_list, key, value);
                else
                    exit_code = print_export_error(key);
            }
            else if (is_valid_identifier(key))
                add_or_update_env_var(env_list, key, "");
            else
                exit_code = print_export_error(key);
            i++;
        }
    }
    return exit_code;
}
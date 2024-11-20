
#include "../lib/minishell.h"

static void	remove_env_var(t_env **env_lst, char *key)
{
	t_env	*current;
	t_env	*prev;

	while (env_lst && *env_lst && key)
	{
		current = *env_lst;
		while (current)
		{
			if (current->key && ft_strcmp(current->key, key) == 0)
			{
				if (current == *env_lst)
					*env_lst = current->next;
				else
					prev->next = current->next;
				free(current->key);
				free(current->value);
				free(current);
				return ;
			}
			prev = current;
			current = current->next;
		}
		return ;
	}
}

static int	check_identifier(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	unset_builtin(char **args, t_env **env_lst)
{
	int	i;
	int	exit_status;

	exit_status = 0;
	if (!args || !args[0])
		return (0);
	i = 0;
	while (args[i])
	{
		if (!check_identifier(args[i]))
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_status = 1;
		}
		else
			remove_env_var(env_lst, args[i]);
		i++;
	}
	return (exit_status);
}

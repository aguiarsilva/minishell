

#include "../lib/minishell.h"

static bool	parse_export_argument(const char *arg, char **key_out, char **value_out)
{
	char	*sign;
	size_t	key_len;

	if (arg == NULL || *arg == '\0')
	{
		fprintf(stderr, "Error: Invalid argument for export: '%s'\n", arg ? arg : "(null)");
		return (false);
	}
	// Find the '=' sign (if it exists)
	sign = ft_strchr_duplicate(arg, '=');
	if (sign)
	{
		if (ft_strchr_duplicate(sign + 1, '='))
		{
			fprintf(stderr, "Error: Invalid argument for export: '%s' (too many '=' signs)\n", arg);
			return (false);
		}
		// Key is everything before '='
		key_len = (size_t)(sign - arg);
		*key_out = ft_strndup(arg, key_len);
		// Value is everything after '='
		*value_out = ft_strdup(sign + 1);
	}
	else
	{
		// No '=': The entire argument is the key, value is empty
		*key_out = ft_strdup(arg);
		*value_out = ft_strdup("");
	}
	return (true);
}

static bool	check_export_argument(char *arg, char **key_out, char **value_out)
{
	// Parse the argument
	if (!parse_export_argument(arg, key_out, value_out))
		return (false); // Parsing failed, error already printed

	// Validate the key
	if (!is_valid_identifier(*key_out, true))
	{
		fprintf(stderr, "Error: '%s' is not a valid identifier for export.\n", *key_out);
		free(*key_out);
		free(*value_out);
		return (false);
	}

	// Handle valid key and optional value
	printf("Valid export argument.\n");
	printf("Key: %s\n", *key_out);
	printf("Value: %s\n", *value_out && **value_out ? *value_out : "(empty)");  // Dereference value_out
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
			fprintf(stderr, "Error: Invalid export format - '=' should not be a separate argument\n");
			return (false);
		}
		// Check if current argument contains '='
		equals = ft_strchr_duplicate(args[i], '=');
		if (equals && i + 1 < arg_count)
		{
			// If next argument starts with '=' or current argument ends with '='
			if (args[i + 1][0] == '=' || equals[1] == '\0')
			{
				fprintf(stderr, "Error: Invalid export format - no spaces allowed around '='\n");
				return (false);
			}
		}
		i++;
	}
	return (true);
}

int	export_builtin(char **args, t_env **env_list)
{
	int		i;
	int		arg_count;
	char	*key;
	char	*value;

	i = 0;
	arg_count = 0;
	key = NULL;
	value = NULL;

	if (args == NULL)
		return (1);
	while (args[arg_count])
		arg_count++;
	if (arg_count == 0)
	{
		printf("DEBUG export no arguments\n");
		print_env_list(*env_list, EXPORT);
		// print_env_list_old(*env_list);
		return (0);
	}
	// Add format validation before processing arguments
	if (!is_valid_export_format(args, arg_count))
		return (1);
	while (i < arg_count)
	{
		if (check_export_argument(args[i], &key, &value) == true)
		{
			printf("DEBUG valid arguments key = %s, value = %s\n", key, value);
			add_or_update_env_var(env_list, key, value);
			free(key);
			free(value);
		}
		i++;
	}
	// print_env_list_old(*env_list);
	return (0);
}

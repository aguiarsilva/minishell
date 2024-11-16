#include "../lib/minishell.h"

bool	is_valid_identifier(const char *key)
{
	int	i;

	i = 0;

	if (!key || (!isalpha(key[0]) && key[0] != '_'))
		return (false);
	while (key[++i])
	{
		if (!isalnum(key[i]) && key[i] != '_')
			return (false);
	}
	return (true);
}

int	print_export_error(const char *key)
{
	fprintf(stderr, "export: `%s': not a valid identifier\n", key);
	return (1);
}

int is_alphanumeric_with_underscores(const char *str)
{
	if (!str || *str == '\0')
		return (0);
	while (*str)
	{
		if (!isalnum(*str) && *str != '_')
		{
			return (0);
		}
		str++;
	}
	return (1);
}

char	*combine_args(char **args, int start)
{
	size_t	combined_length;
	char	*combined_str;
	char*	final_combined_str;
	// Check if the array contains at least three elements
	if (start > 0)
		start = start + 2;
	if (!args || !args[start] || !args[start + 1] || !args[start + 2])
	{
		fprintf(stderr, "Error: Expected at least 3 arguments in the array\n");
		return (NULL);
	}
	// Validate the contents of args[0], args[1], and args[2]
	if (!is_alphanumeric_with_underscores(args[start]))
	{
		fprintf(stderr, "Error: args[0] must be alphanumeric with underscores only\n");
		return (NULL);
	}

	if (ft_strcmp(args[start + 1], "=") != 0)
	{
		fprintf(stderr, "Error: args[1] must be an equals sign\n");
		return (NULL);
	}

	if (!is_alphanumeric_with_underscores(args[start + 2]))
	{
		fprintf(stderr, "Error: args[2] must be alphanumeric with underscores only\n");
		return NULL;
	}
	// Calculate length for the combined string: args[0] + "=" + args[2] + null terminator
	combined_length = strlen(args[start + 1]) + 1 + strlen(args[start + 2]) + 1;
	combined_str = malloc(combined_length);
	if (!combined_str)
	{
		perror("malloc failed");
		return (NULL);
	}

	// // Combine args[0], args[1], and args[2] into "args[0]=args[2]" format
	combined_str = ft_strjoin(args[start], "="); // Join args[0] with "="
	if (combined_str)
	{
		final_combined_str = ft_strjoin(combined_str, args[start + 2]); // Now join the result with args[2]
		free(combined_str); // Don't forget to free the intermediate string
		return (final_combined_str);
	}
}

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	len;
	size_t	copy_len;
	char	*dest;

	len = ft_strlen(s1);
	if (len < n)
		copy_len = len;
	else
		copy_len = n;
	dest = malloc(copy_len + 1);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, s1, copy_len);
	dest[copy_len] = '\0';
	return (dest);
}

bool	parse_export_argument(const char *arg, char **key_out, char **value_out)
{
	char	*sign;
	size_t	key_len;

	if (!arg || *arg == '\0')
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
		*value_out = ft_strdup(""); // Empty value
	}
	return (true);
}

bool	check_export_argument(char *arg, char **key_out, char **value_out)
{
	// Parse the argument
	if (!parse_export_argument(arg, key_out, value_out))
		return (false); // Parsing failed, error already printed

	// Validate the key
	if (!is_valid_identifier(*key_out))
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

int	export_builtin(char **args, t_env **env_list) // write a new print export cmd and don't use print env
{
	int i = 0;
	int arg_count = 0;
	char *key;
	char *value;

	key = NULL;
	value = NULL;
	if (args == NULL)
		return (0);
	printf(" in export_builtin\n");
	// Count number of arguments
	while (args[arg_count])
	{
		printf("args in export[%d]: %s\n", arg_count, args[arg_count]);
		arg_count++;
	}
	printf("arg count in export = %d\n", arg_count);
	if (args[0] == NULL)
	{
		printf("export no arguments\n");
		print_env_list(*env_list);
		return (0);
	}
	while (i < arg_count)
	{
		if (check_export_argument(args[i], &key, &value) == true)
		{
			printf("valid arguments key = %s, value =%s\n", key, value);
			add_or_update_env_var(env_list, key, value);
//			free(key);
//			free(value);
			print_env_list(*env_list); // only for debug
		}
		i++;
	}
	return (0);
}

//bool	check_export_argument(char *arg)
//{
//	char	*sign;
//	char	*key;
//	char	*value;
//	size_t	key_len;
//
//	if (!arg || *arg == '\0')
//	{
//		fprintf(stderr, "Error: Invalid argument for export: '%s'\n", arg ? arg : "(null)");
//		return (false);
//	}
//	// Find the '=' sign (if it exists)
//	sign = ft_strchr_duplicate(arg, '=');
//	if (sign)
//	{
//		// Key is everything before '='
//		key_len = (size_t)(sign - arg);
//		key = ft_strndup(arg, key_len);
//		// Value is everything after '='
//		value = ft_strdup(sign + 1);
//	}
//	else
//	{
//		// No '=': The entire argument is the key, value is empty
//		key = ft_strdup(arg);
//		value = ft_strdup(""); // Empty value
//	}
//	// Validate the key
//	if (!is_valid_identifier(key))
//	{
//		fprintf(stderr, "Error: '%s' is not a valid identifier for export.\n", key);
//		free(key);
//		free(value);
//		return (false);
//	}
//	// Handle valid key and optional value
//	printf("Valid export argument.\n");
//	printf("Key: %s\n", key);
//	printf("Value: %s\n", *value ? value : "(empty)");
//	free(key);
//	free(value);
//	return (true);
//}

//int	export_builtin(char** args, t_env** env_list) // an else case is missing // oldversion not working properly
//{
//	int exit_code = 0;
//	int i = 0;
//	char* one_set_of_export;
//	bool valid_export = false;
//	char* sign;
//	char* key;
//	char* value;
//
//	if (args == NULL)
//		return 0;
//
//	printf(" in export_builtin\n");
//
//	// Count number of arguments
//	while (args[i])
//	{
//		i++;
//	}
//	printf("i = %d\n", i);
//	if (args[0] == NULL)
//	{
//		printf("export no arguments");
//		print_env_list(*env_list);
//		return (0);
//	}
//	//
//	if (args[0] && args[1] == NULL) // combine them if no spaces are there
//	{
//		sign = ft_strchr_duplicate(args[0], '=');
//		key = ft_strtrim(args[0], sign);
//		value = ft_strtrim(sign + 1, " ");
//		// fprintf(stderr, "key :%s\n", key);
//		// fprintf(stderr, "sign :%s\n", sign);
//		// fprintf(stderr, "value :%s\n", value);
//		if (is_valid_identifier(key))
//		{
//			add_or_update_env_var(env_list, key, value);
//			print_env_list(*env_list);
//		}
//	}
//	// Case 1: If there are more than 2 arguments, handle them
//	if (i > 2)
//	{
//		int s = 0;
//		int start = 0;
//		// Combine args[0], args[1], args[2] into a single "key=value" string
//		int loop_counter = (i / 3);
//		printf("loop counter  %d\n", loop_counter);
//		while (s < loop_counter)
//		{
//			printf("start %d\n", s);
//			start = s;
//			one_set_of_export = combine_args(args, start);
//			if (one_set_of_export)
//			{
//				printf("exportexample: %s\n", one_set_of_export);
//				sign = ft_strchr_duplicate(one_set_of_export, '=');
//
//				if (sign)
//				{
//					// fprintf(stderr, "sign :%s\n", sign);
//
//					// Split the combined string into key and value
//					key = ft_strtrim(one_set_of_export, sign);
//					// fprintf(stderr, "key :%s\n", key);
//
//					value = ft_strtrim(sign + 1, " "); // Skip the '=' and trim spaces
//					// fprintf(stderr, "value :%s\n", value);
//
//					valid_export = true;
//
//					// Add the key-value pair to the environment
//					if (is_valid_identifier(key))
//					{
//						add_or_update_env_var(env_list, key, value);
//						printf("added value \n");
//						print_env_list(*env_list);
//					}
//				}
//			}
//			s++;
//		}
//	}
//		// Case 2: If there is only one argument (e.g., "export API_KEY")
//	else if (i == 1)
//	{
//		key = args[0];
//		if (is_valid_identifier(key))
//		{
//			add_or_update_env_var(env_list, key, "");
//			print_env_list(*env_list);
//		}
//		return 0;
//	}
//
//	// Process any additional arguments (new keys with empty values)
//	if (i % 2 + 1)
//	{
//		int j = i - 1;
//		// int j = 3; // Initialize the counter
//
//		while (j < i)
//		{
//			// Loop until j is less than i
//			printf("should not loop \n");
//			key = args[j];
//			if (is_valid_identifier(key))
//			{
//				add_or_update_env_var(env_list, key, ""); // New key with empty value
//				print_env_list(*env_list);
//			}
//			j++; // Increment the counter
//		}
//	}
//	return exit_code;
//}
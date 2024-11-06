#include "../lib/minishell.h"

int is_valid_identifier(const char* key)
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

int print_export_error(const char* key)
{
	fprintf(stderr, "export: `%s': not a valid identifier\n", key);
	return 1;
}

int is_alphanumeric_with_underscores(const char* str)
{
	if (!str || *str == '\0') return 0; // Empty string not allowed
	while (*str)
	{
		if (!isalnum(*str) && *str != '_')
		{
			return 0;
		}
		str++;
	}
	return 1;
}

char* combine_args(char** args, int start)
{
	// Check if the array contains at least three elements
	if (start > 0)
	{
		start = start + 2;
	}
	if (!args || !args[start] || !args[start + 1] || !args[start + 2])
	{
		fprintf(stderr, "Error: Expected at least 3 arguments in the array\n");
		return NULL;
	}

	// Validate the contents of args[0], args[1], and args[2]
	if (!is_alphanumeric_with_underscores(args[start]))
	{
		fprintf(stderr, "Error: args[0] must be alphanumeric with underscores only\n");
		return NULL;
	}

	if (strcmp(args[start + 1], "=") != 0)
	{
		fprintf(stderr, "Error: args[1] must be an equals sign\n");
		return NULL;
	}

	if (!is_alphanumeric_with_underscores(args[start + 2]))
	{
		fprintf(stderr, "Error: args[2] must be alphanumeric with underscores only\n");
		return NULL;
	}

	// Calculate length for the combined string: args[0] + "=" + args[2] + null terminator
	size_t combined_length = strlen(args[start + 1]) + 1 + strlen(args[start + 2]) + 1;
	char* combined_str = malloc(combined_length);
	if (!combined_str)
	{
		perror("malloc failed");
		return NULL; // Allocation failed
	}

	// // Combine args[0], args[1], and args[2] into "args[0]=args[2]" format
	// snprintf(combined_str, combined_length, "%s=%s", args[0], args[2]);
	// return combined_str;
	combined_str = ft_strjoin(args[start], "="); // Join args[0] with "="
	if (combined_str)
	{
		char* final_combined_str = ft_strjoin(combined_str, args[start + 2]); // Now join the result with args[2]
		free(combined_str); // Don't forget to free the intermediate string
		return final_combined_str;
	}
}

int	export_builtin(char** args, t_env** env_list)
{
	int exit_code = 0;
	int i = 0;
	char* one_set_of_export;
	bool valid_export = false;
	char* sign;
	char* key;
	char* value;

	if (args == NULL)
		return 0;

	printf(" in export_builtin\n");

	// Count number of arguments
	while (args[i])
	{
		i++;
	}
	printf("i = %d\n", i);
	if (args[0] && args[1] == NULL) // combine them if no spaces are there
	{
		sign = ft_strchr(args[0], '=');
		key = ft_strtrim(args[0], sign);
		value = ft_strtrim(sign + 1, " ");
		// fprintf(stderr, "key :%s\n", key);
		// fprintf(stderr, "sign :%s\n", sign);
		// fprintf(stderr, "value :%s\n", value);
		if (is_valid_identifier(key))
		{
			add_or_update_env_var(env_list, key, value);
			print_env_list(*env_list);
		}
	}
	// Case 1: If there are more than 2 arguments, handle them
	if (i > 2)
	{
		int s = 0;
		int start = 0;
		// Combine args[0], args[1], args[2] into a single "key=value" string
		int loop_counter = (i / 3);
		printf("loop counter  %d\n", loop_counter);
		while (s < loop_counter)
		{
			printf("start %d\n", s);
			start = s;
			one_set_of_export = combine_args(args, start);
			if (one_set_of_export)
			{
				printf("exportexample: %s\n", one_set_of_export);
				sign = ft_strchr(one_set_of_export, '=');

				if (sign)
				{
					// fprintf(stderr, "sign :%s\n", sign);

					// Split the combined string into key and value
					key = ft_strtrim(one_set_of_export, sign);
					// fprintf(stderr, "key :%s\n", key);

					value = ft_strtrim(sign + 1, " "); // Skip the '=' and trim spaces
					// fprintf(stderr, "value :%s\n", value);

					valid_export = true;

					// Add the key-value pair to the environment
					if (is_valid_identifier(key))
					{
						add_or_update_env_var(env_list, key, value);
						printf("added value \n");
						print_env_list(*env_list);
					}
				}
			}
			s++;
		}
	}
	// Case 2: If there is only one argument (e.g., "export API_KEY")
	else if (i == 1)
	{
		key = args[0];
		if (is_valid_identifier(key))
		{
			add_or_update_env_var(env_list, key, "");
			print_env_list(*env_list);
		}
		return 0;
	}

	// Process any additional arguments (new keys with empty values)
	if (i % 2 + 1)
	{
		int j = i - 1;
		// int j = 3; // Initialize the counter

		while (j < i)
		{
			// Loop until j is less than i
			printf("should not loop \n");
			key = args[j];
			if (is_valid_identifier(key))
			{
				add_or_update_env_var(env_list, key, ""); // New key with empty value
				print_env_list(*env_list);
			}
			j++; // Increment the counter
		}
	}
	return exit_code;
}

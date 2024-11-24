
#include "../lib/minishell.h"

int	is_valid_number(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	builtin_exit(t_cmd *cmd, t_env *env)
{
	char	*exitcode_str;
	int		exit_code;

	printf("builtin exit\n");
	if (!cmd->args[0])
	{
		// If no arguments, use the last exit code from env
		exitcode_str = get_key_in_env_lst(env, "EC");
		exit_code = ft_atoi(exitcode_str);
		printf("DEBUG: exitcode with no arguments = %d\n", exit_code);
		free(exitcode_str);
		exit(exit_code);
	}
	if (!is_valid_number(cmd->args[0]))
	{
		fprintf(stderr, EXIT_NUMERIC_ARG_REQ);
		exit(255);
	}
	if (cmd->args[1])
	{
		fprintf(stderr, EXIT_TOO_MANY_ARGS);
		return (1);
	}
	exit_code = (unsigned char)ft_atoll(cmd->args[0]);
	// Update the exit code in both cmd and env structures
//	cmd->exit_code = exit_code;
//	env->exit_code = exit_code;
	fprintf(stderr, "exit_code: %d when using builtin exit \n", exit_code);
	exit(exit_code);
}

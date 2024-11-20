

#include "../lib/minishell.h"

static void	print_env_var(t_env *env)
{
	if (ft_strncmp(env->key, "EC", 2) == 0)
		return ;
	if (env->value) // Only print if the variable has a value
	{
		ft_putstr_fd(env->key, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(env->value, 1);
		ft_putchar_fd('\n', 1);
	}
}

// static int	is_option(const char *arg)
// {
// 	return (arg && arg[0] == '-');
// }
void	print_env_list(t_env *env_lst)
{
	bool	printed_ec;
	int		exit_code;

	printed_ec = false;
	exit_code	= 0;
	while (env_lst)
	{
		print_env_var(env_lst);
		if (ft_strncmp(env_lst->key, "EC", 2) == 0)
		{
			printed_ec = true;
			exit_code = env_lst->exit_code;
		}
		env_lst = env_lst->next;
	}
	if (printed_ec)
	{
		ft_putstr_fd("EC=", STDOUT_FILENO);
		ft_putnbr_fd(exit_code, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO); // Ensure a newline after printing EC
	}
}

int	env_builtin(t_cmd *cmd_data, t_env *env_lst)
{
	if (cmd_data->args && cmd_data->args[0])
	{
		if (cmd_data->args[0][0] == '-')
		{
			ft_putstr_fd("env: illegal option -- ", 2);
			ft_putchar_fd(cmd_data->args[0][1], 2);
			ft_putstr_fd("\nusage: env\n", 2);
			return (1);
		}
		else
		{
			ft_putstr_fd("env: '", 2);
			ft_putstr_fd(cmd_data->args[0], 2);
			ft_putstr_fd("': No such file or directory\n", 2);
			return (127);
		}
	}
	print_env_list(env_lst);
	return (0);
}

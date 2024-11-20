#include "../lib/minishell.h"

static bool	has_n_flag(t_cmd *cmd_data)
{
	int	i;

	i = 1;
	if (cmd_data->args[0] && cmd_data->args[0][0] == '-')
	{
		while (cmd_data->args[0][i] == 'n')
			i++;
		if (cmd_data->args[0][i] == '\0')
			return (true);
	}
	return (false);
}

// int	echo(t_cmd *cmd_data)
// {
// 	int		i;
// 	bool	n_flag;

// 	i = has_n_flag(cmd_data);
// 	n_flag = i;
// 	while (cmd_data->args[i])
// 	{
// 		ft_putstr_fd(cmd_data->args[i], STDOUT_FILENO);
// 		if (cmd_data->args[i + i])
// 			ft_putchar_fd(' ', 1);
// 		i++;
// 	}
// 	if (!n_flag)
// 		ft_putchar_fd('\n', 1);
// 	return (0);
// }

static void	print_escaped_string(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			i++;
			if (!str[i]) // if backslash is the last character
			{
				ft_putchar_fd('\\', STDOUT_FILENO);
				break;
			}
			if (str[i] == 'n')
				ft_putchar_fd('n', STDOUT_FILENO);
			else if (str[i] == 't')
				ft_putchar_fd('t', STDOUT_FILENO);
			else
				ft_putchar_fd(str[i], STDOUT_FILENO);
		}
		else
			ft_putchar_fd(str[i], STDOUT_FILENO);
		i++;
	}
}

int	echo(t_cmd *cmd_data)
{

	int		i;
	bool	n_flag;

	i = has_n_flag(cmd_data);
	n_flag = i;
	while (cmd_data->args[i])
	{
		if (cmd_data->args[i][0] == '\\' && cmd_data->args[i][1])
			print_escaped_string(cmd_data->args[i]);
		else
			ft_putstr_fd(cmd_data->args[i], STDOUT_FILENO);
		if (cmd_data->args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

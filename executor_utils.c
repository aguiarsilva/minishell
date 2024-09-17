#include "lib/minishell.h"

void	ft_free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*get_env_value_by_name(char *envVarName, char **env)
{
	int		i;
	char	*equal_sign_pos;
	char	*path;

	i = 0;
	if (*env == NULL)
		return ("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:");
	while (env[i])
	{
		if (ft_strncmp(env[i], envVarName, ft_strlen(envVarName)) == 0)
		{
			equal_sign_pos = ft_strchr(env[i], '=');
			if (equal_sign_pos)
			{
				path = equal_sign_pos + 1;
				return (path);
			}
		}
		i++;
	}
	return (NULL);
}

char	*get_exec_path(char *cmd, char **env)
{
	int		i;
	char	*exec_path;
	char	**path_list;
	char	*current_path;
	char	**s_cmd;

	i = -1;
	path_list = ft_split(get_env_value_by_name("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (path_list[++i])
	{
		current_path = ft_strjoin(path_list[i], "/");
		exec_path = ft_strjoin(current_path, s_cmd[0]); // maybe change 0 to a new variable
//because the input could start with something else ?
		//fprintf(stderr, "current_path: %s\n", current_path);
		//fprintf(stderr, "exec_path: %s\n", exec_path);
		free(current_path);
		if (access(exec_path, X_OK) == 0)
		{
			ft_free_array(s_cmd);
			return (exec_path);
		}
		free(exec_path);
	}
	ft_free_array(path_list);
	ft_free_array(s_cmd);
	print_error_cmd_not_found_and_exit(cmd);
	return (NULL);
}

char	**parse_command_with_quotes(char *cmd)
{
	int		c_index;
	char	quote_marker;
	char	**split_cmd;

	c_index = -1;
	while (cmd[++c_index])
	{
		if (cmd[c_index] == ' ')
			cmd[c_index] = '\x1A';
		if (cmd[c_index] == '\'' || cmd[c_index] == '\"')
		{
			quote_marker = cmd[c_index];
			cmd[c_index] = '\x1A';
			while (cmd[c_index] != quote_marker && cmd[c_index])
				c_index++;
			cmd[c_index] = '\x1A';
		}
	}
	split_cmd = ft_split(cmd, '\x1A');
	return (split_cmd);
}
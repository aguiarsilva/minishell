/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:25:45 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/11/26 11:48:14 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

bool	handle_no_arguments(t_env **env_list, int arg_count)
{
	if (arg_count == 0)
	{
		print_env_list(*env_list, EXPORT);
		return (true);
	}
	return (false);
}

bool	is_valid_identifier(const char *key, bool check_first_char)
{
	int	i;

	i = 0;
	if (key == NULL || *key == '\0')
		return (false);
	if (check_first_char && (!ft_isalpha(key[0]) && key[0] != '_'))
		return (false);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (false);
		i++;
	}
	return (true);
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
	if (dest == NULL)
		return (NULL);
	ft_memcpy(dest, s1, copy_len);
	dest[copy_len] = '\0';
	return (dest);
}

int	count_arg_from_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

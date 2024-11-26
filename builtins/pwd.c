/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:26:00 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/11/26 11:26:03 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	pwd(void)
{
	char	*current_work_directory;

	current_work_directory = getcwd(NULL, 0);
	if (!current_work_directory)
	{
		perror("getcwd");
		free(current_work_directory);
		return (1);
	}
	printf("%s\n", current_work_directory);
	free(current_work_directory);
	return (0);
}

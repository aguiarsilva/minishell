/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:39:34 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/11/28 15:39:34 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	open_input_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_error_msg_and_exit(ERR_FILE);
	return (fd);
}

int	open_output_file(const char *filename, int mode)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | mode, 0644);
	if (fd == -1)
		print_error_msg_and_exit(ERR_FILE);
	return (fd);
}

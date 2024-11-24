/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:17:39 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/11/24 23:35:52 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>

char	*get_next_line(int fd);

void	*ft_calloc_complete(size_t count, size_t size);
char	*ft_strchr_duplicate(const char *s, int c);
char	*initialize_line_read_if_null(char *line_read);
size_t	ft_strlen(const char *s);
size_t	find_newline_pos(const char *str);

#endif

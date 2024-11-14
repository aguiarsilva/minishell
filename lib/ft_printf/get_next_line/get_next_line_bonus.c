/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:18:16 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/02/23 18:50:49 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*remove_old_string_from_rest_buffer(char *rest_buf)
{
	char	*cleaned_restbuf;
	size_t	char_index;
	size_t	newline_pos;
	size_t	past_new_line;
	size_t	cleaned_buf_len;

	char_index = 0;
	newline_pos = find_newline_pos(rest_buf);
	if (rest_buf[newline_pos] == '\0')
	{
		free(rest_buf);
		return (NULL);
	}
	past_new_line = 1;
	cleaned_buf_len = (ft_strlen(rest_buf)) - newline_pos;
	cleaned_restbuf = ft_calloc_complete(cleaned_buf_len + 1, sizeof(char));
	while (rest_buf[newline_pos + past_new_line])
	{
		cleaned_restbuf[char_index] = rest_buf[newline_pos + past_new_line];
		char_index++;
		past_new_line++;
	}
	cleaned_restbuf[char_index] = '\0';
	free(rest_buf);
	return (cleaned_restbuf);
}

char	*extract_line_up_to_new_line(char *rest_buf)
{
	char		*line;
	size_t		char_index;
	size_t		offset;

	char_index = 0;
	offset = 1;
	if (rest_buf[0] == '\0')
		return (NULL);
	char_index = find_newline_pos(rest_buf);
	if (rest_buf[char_index] == '\n')
		offset = 2;
	else
		offset = 1;
	line = ft_calloc_complete(char_index + offset, sizeof(char));
	char_index = 0;
	while (rest_buf[char_index] != '\n' && rest_buf[char_index])
	{
		line[char_index] = rest_buf[char_index];
		char_index++;
	}
	if (rest_buf[char_index] == '\n')
		line[char_index++] = '\n';
	return (line);
}

char	*ft_strjoin_and_free(char *previous_read, char *current_read)
{
	char	*complete_line;
	int		total_length;
	int		char_index;
	int		char_index2;

	total_length = ft_strlen(previous_read) + ft_strlen(current_read);
	complete_line = malloc((total_length + 1) * sizeof(char));
	if (complete_line == NULL)
		return (NULL);
	char_index = 0;
	char_index2 = 0;
	while (previous_read[char_index] != '\0')
		complete_line[char_index2++] = previous_read[char_index++];
	char_index = 0;
	while (current_read[char_index] != '\0')
		complete_line[char_index2++] = current_read[char_index++];
	complete_line[char_index2] = '\0';
	free(previous_read);
	return (complete_line);
}

char	*read_file(int fd, char *line_read)
{
	char		*read_buffer;
	ssize_t		bytes_read;

	line_read = initialize_line_read_if_null(line_read);
	if (!line_read)
		return (NULL);
	read_buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!read_buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(read_buffer);
			return (NULL);
		}
		read_buffer[bytes_read] = '\0';
		line_read = ft_strjoin_and_free(line_read, read_buffer);
		if (ft_strchr_duplicate(read_buffer, '\n'))
			break ;
	}
	free(read_buffer);
	return (line_read);
}
// line_read holds the read content of a file by line line
// line_read holds the read content until eof or the first \n
// is encountered but it can also include a string containing \n 
// because the the read buffer does not stop when \n is encountered. 
// That means breaks out of the loop only stops
// after the first \n is encountered.

char	*get_next_line(int fd)
{
	static char	*rest_buf[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (rest_buf[fd])
		{
			free(rest_buf[fd]);
			rest_buf[fd] = 0;
		}
		return (NULL);
	}
	rest_buf[fd] = read_file(fd, rest_buf[fd]);
	if (!rest_buf[fd])
		return (NULL);
	line = extract_line_up_to_new_line(rest_buf[fd]);
	rest_buf[fd] = remove_old_string_from_rest_buffer(rest_buf[fd]);
	return (line);
}
// in the end the rest_buf stores
// the remainder of what was read but not printed. 

// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// #include "get_next_line.h"

// int	main(void)
// {
// 	int	fd1;
// 	int	fd2;

// 	fd1 = open("file1.txt", O_RDONLY);
// 	fd2 = open("file2.txt", O_RDONLY);
// 	if (fd1 == -1 || fd2 == -1)
// 	{
// 		perror("open");
// 		exit(1);
// 	}
// 	char *line1 = NULL;
// 	char *line2 = NULL;
// 	while (1)
// 	{
// 		if (line1 == NULL)
// 		{
// 			line1 = get_next_line(fd1);
// 			if (line1 == NULL)
// 			{
// 				close(fd1);
// 				fd1 = -1;
// 			}
// 		}
// 		if (line2 == NULL)
// 		{
// 			line2 = get_next_line(fd2);
// 			if (line2 == NULL)
// 			{
// 				close(fd2);
// 				fd2 = -1;
// 			}
// 		}
// 		if (line1 != NULL)
// 		{
// 			printf("fd1: %s\n", line1);
// 			free(line1);
// 			line1 = NULL;
// 		}
// 		if (line2 != NULL)
// 		{
// 			printf("fd2: %s\n", line2);
// 			free(line2);
// 			line2 = NULL;
// 		}
// 		if (fd1 == -1 && fd2 == -1)
// 			break ;
// 	}
// 	return (0);
// }

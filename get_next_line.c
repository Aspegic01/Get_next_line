/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:42:11 by mlabrirh          #+#    #+#             */
/*   Updated: 2024/11/28 12:53:56 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **buffer)
{
	char	*newline_pos;
	char	*line;
	char	*new_buffer;
	size_t	len;

	newline_pos = ft_strchr(*buffer, '\n');
	if (newline_pos)
	{
		len = newline_pos - *buffer + 1;
		line = malloc(len + 1);
		if (!line)
			return (NULL);
		ft_memcpy(line, *buffer, len);
		line[len] = '\0';
		new_buffer = ft_strdup(newline_pos + 1);
		free(*buffer);
		*buffer = new_buffer;
	}
	else
	{
		line = *buffer;
		*buffer = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*temp;
	char		*new_buffer;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc(1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
	{
		free(buffer);
		return (NULL);
	}
	while (!ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		temp[bytes_read] = '\0';
		new_buffer = ft_strjoin(buffer, temp);
		free(buffer);
		buffer = new_buffer;
		if (!buffer)
		{
			free(temp);
			return (NULL);
		}
	}
	free(temp);
	if (!buffer || buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	return (extract_line(&buffer));
}

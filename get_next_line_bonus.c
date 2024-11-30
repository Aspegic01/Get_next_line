/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:48:17 by mlabrirh          #+#    #+#             */
/*   Updated: 2024/11/30 09:31:59 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static char	*get_lines(int fd, char *str, char *buffer)
{
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (!str)
			str = ft_strdup("");
		temp = ft_strjoin(str, buffer);
		free(str);
		if (!temp)
			return (NULL);
		str = temp;
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0)
	{
		free(str);
		str = NULL;
	}
	return (str);
}

static char	*read_line(char *line)
{
	int		i;
	char	*str;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (NULL);
	str = ft_strdup(line + i + 1);
	if (!str || *str == '\0')
	{
		free(str);
		str = NULL;
	}
	line[i + 1] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buffer[fd];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(str);
		return (str);
	}
	buffer[fd] = malloc(((size_t)BUFFER_SIZE + 1));
	if (!buffer[fd])
		return (NULL);
	line = get_lines(fd, str, buffer[fd]);
	free(buffer[fd]);
	if (!line)
	{
		free(str);
		return (NULL);
	}
	str = read_line(line);
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:56:11 by trupham           #+#    #+#             */
/*   Updated: 2025/04/30 16:50:12 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdio.h>

static char *build_line(int fd, char *line)
{	
	ssize_t bytes;
	char *buff;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (free(line), NULL);
	bytes = 1;
	while (bytes > 0 && !has_nl(line))
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			if (line)
				free(line);
			return (free(buff), NULL);
		}
		buff[bytes] = 0;
		line = ft_strjoin(line, buff);
		if (!line)
			return (free(buff), free(line), NULL);
	}
	free(buff);
	return line;
}

char *get_next_line(int fd)
{
	static char *line;
	char *newline;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = build_line(fd, line);
	if (!line || ft_strlen(line) == 0)
	{
		return (free(line), NULL);
	}

	// INFO: get new line.
	int line_length = 0;
	int i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			line_length++;
			break;
		}
		else
			line_length++;
		i++;
	}
	newline = malloc(line_length + 1);
	if (!newline)
		return (free(line), line = NULL, NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			newline[i++] = '\n';
			break;
		}
		else
			newline[i] = line[i];
		i++;
	}
	newline[i] = 0;

	// INFO: clean up. line is the strings after \n. i = position after \n
	char *leftover;
	int k = i;
	line_length = 0;
	while (line[i++])
		line_length++;
	leftover = malloc(line_length + 1);
	if (!leftover)
		return (free(line), free(newline), NULL);
	int j = 0;
	while (line[k])
		leftover[j++] = line[k++];
	leftover[j] = 0;
	free(line);
	line = leftover;
	return (newline);
}

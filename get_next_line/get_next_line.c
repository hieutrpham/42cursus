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

char *get_next_line(int fd)
{
	static char *line;
	char *buff;
	char *newline;
	ssize_t bytes;
	char *tmp;
	int i;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return NULL;
	bytes = 1;
	// INFO: build line from buffer
	while (bytes > 0 && !has_nl(line))
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes <= 0)
			break;
		buff[bytes] = 0;
		if (!line)
			line = ft_strdup("");
		line = ft_strjoin(line, buff);
	}
	if (bytes < 0)
		return (free(buff), NULL);
	// INFO: get new line
	if (ft_strlen(line) == 0)
		return (free(buff), NULL);
	newline = malloc(ft_strlen(line) + 1);
	if (!newline)
		return (free(buff), NULL);
	i = 0;
	while (*line)
	{
		if (*line == '\n')
		{
			newline[i++] = '\n';
			break;
		}
		else
			newline[i++] = *line++;
	}
	newline[i] = 0;
	// INFO: clean up. line is the strings after \n
	while (*line == '\n')
		line++;
	free(buff);
	return (newline);
}

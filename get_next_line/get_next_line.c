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

char *get_next_line(int fd)
{
	static char *leftover;
	char *buff;
	char *line;
	char *newline;
	ssize_t bytes;
	int i;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return NULL;
	// INFO: build line from buffer
	while (1)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes <= 0)
			return (free(buff), NULL);
		if (has_nl(buff) || bytes < BUFFER_SIZE)
			break;
		buff[bytes] = 0;
		if (!leftover)
			leftover = ft_strdup("");
		leftover = ft_strjoin(leftover, buff);
	}
	i = 0;
	line = ft_strjoin(leftover, buff);
	// INFO: get new line
	newline = malloc(ft_strlen(line) + 1);
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
	// INFO: clean up. leftover is the strings after \n
	char *temp = buff;
	while (*buff && *buff != '\n')
		buff++;
	leftover = ft_substr(buff, 1, ft_strlen(temp) - ft_strlen(buff));
	return (newline);
}

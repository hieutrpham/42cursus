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
	static char *leftover;
	char *buff;
	char *line;
	char *newline;
	ssize_t bytes;
	int i;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return NULL;
	bytes = 1;
	// INFO: build line from buffer
	while (bytes > 0 && !has_nl(leftover))
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes <= 0)
			break;
		buff[bytes] = 0;
		if (!leftover)
			leftover = ft_strdup("");
		leftover = ft_strjoin(leftover, buff);
	}
	if (bytes < 0)
		return (free(buff), NULL);
	// INFO: get new line
	if (ft_strlen(leftover) == 0)
		return (free(buff), NULL);
	newline = malloc(ft_strlen(leftover) + 1);
	if (!newline)
		return (free(buff), NULL);
	i = 0;
	while (*leftover)
	{
		if (*leftover == '\n')
		{
			newline[i++] = '\n';
			break;
		}
		else
			newline[i++] = *leftover++;
	}
	newline[i] = 0;
	// INFO: clean up. leftover is the strings after \n
	while (*leftover == '\n')
		leftover++;
	free(buff);
	return (newline);
}

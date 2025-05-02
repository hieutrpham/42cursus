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
	t_list *node;

	node = malloc(sizeof(t_list));
	node->content = malloc(BUFFER_SIZE + 1);
	ssize_t bytes_read = read(fd, node->content, BUFFER_SIZE);
	char *result = node->content;
	free(node);
	result[bytes_read] = '\0';
	return result;
}

int main()
{
	int fd = open("hello.txt", O_RDONLY);
	char *line;

	printf("%s\n", line = get_next_line(fd));
	free(line);
	printf("%s\n", line = get_next_line(fd));
	free(line);
	printf("%s\n", line = get_next_line(fd));
	free(line);
	printf("%s\n", line = get_next_line(fd));
	free(line);
	printf("%s\n", line = get_next_line(fd));
	free(line);
	printf("%s\n", line = get_next_line(fd));
	free(line);
	close(fd);
	return 0;
}

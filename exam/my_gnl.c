#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif /* ifndef BUFFER_SIZE */

char *get_line(char *str, int start, int end)
{
	char *line;

	line = malloc(end - start + 1);
	int i = 0;
	for (i = 0; i < end - start; i++)
		line[i] = str[start + i];
	line[i] = 0;
	return line;
}

char *get_next_line(int fd)
{
	char buf[BUFFER_SIZE];
	static char cache[1000000];
	static int start;
	static int end;
	int bytes = 0;

	while (1)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes > 0)
		{
			for (int i = 0; i < bytes; i ++)
				cache[end++] = buf[i];
			continue;
		}
		else if (bytes < 0)
			return 0;
		else
			break;
	}

	if (start == end) return 0;

	for (int i = start; i < end; i++)
	{
		if (cache[i] == '\n')
		{
			char *line = get_line(cache, start, i + 1);
			start = i + 1;
			return line;
		}
	}

	char *line = get_line(cache, start, end);
	start = end;
	return line;
}

#include <fcntl.h>
int main(int ac, char **av)
{
	int fd = open(av[1], O_RDONLY);
	
	while (1)
	{
		char *line = get_next_line(fd);
		if (!line)
			break;
		printf("%s", line);
		free(line);
	}
}

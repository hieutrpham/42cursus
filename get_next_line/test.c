#include "get_next_line.h"
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd = open("hello.txt", O_RDONLY);
    int fd1 = open("nl.txt", O_RDONLY);
    int fd2 = open("no_nl.txt", O_RDONLY);
	t_list *line;
	t_list *tmp;

	line = get_next_line(fd);
	tmp = line;
	while (tmp)
	{
		fprintf(stderr, "DEBUGPRINT[8]: test.c:15: tmp=%s\n", tmp->content);
		tmp = tmp->next;
	}
	ft_free(&line);
    return 0;
}

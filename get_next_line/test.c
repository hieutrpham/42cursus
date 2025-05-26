#include "get_next_line.h"
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd = open("hello.txt", O_RDONLY);
    int fd1 = open("nl.txt", O_RDONLY);
    int fd2 = open("no_nl.txt", O_RDONLY);
	char *line;

	while ((line = get_next_line(fd)))
	{
		puts("===================");
		fprintf(stderr, "DEBUGPRINT[8]: test.c:15: line=%s\n", line);
		free(line);
	}
    return 0;
}

#include "get_next_line.h"
#include <assert.h>
#include <string.h>

int main() {
    int fd = open("hello.txt", O_RDONLY);
    int fd1 = open("nl.txt", O_RDONLY);
    int fd2 = open("no_nl.txt", O_RDONLY);
	char *line;

	for (int i = 0; i < 13; i++)
	{
		line = get_next_line(fd2);
		fprintf(stderr, "DEBUGPRINT[4]: test.c:9: line=%s", line);
	}

    return 0;
}

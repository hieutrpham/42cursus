#include "get_next_line.h"
#include <assert.h>
#include <stdio.h>
#include <fcntl.h>

int main() {
    int fd = open("hello.txt", O_RDONLY);
    int fd1 = open("gnlTester/files/empty", O_RDONLY);
    int fd2 = open("gnlTester/files/41_no_nl", O_RDONLY);
    int fd3 = open("gnlTester/files/42_with_nl", O_RDONLY);
	char *line;

	while((line = get_next_line(fd)))
	{
		fprintf(stderr, "DEBUGPRINT[4]: test.c:9: line=%s", line);
		free(line);
	}

	// line = get_next_line(fd);
	// fprintf(stderr, "DEBUGPRINT[19]: test.c:14: line=%s\n", line);

    return 0;
}

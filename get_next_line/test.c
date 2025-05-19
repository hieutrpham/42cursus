#include "get_next_line.h"
#include <assert.h>
#include <string.h>

int main() {
    int fd = open("hello.txt", O_RDONLY);
    int fd1 = open("nl.txt", O_RDONLY);
    int fd2 = open("no_nl.txt", O_RDONLY);
	char *line;

	line = get_next_line(fd2);
	fprintf(stderr, "DEBUGPRINT[4]: test.c:9: line=%s", line);
	assert(!has_newline(line));
	// assert(strcmp(line, "012345678901234567890123456789012345678901")==0);
    close(fd1);

    return 0;
}

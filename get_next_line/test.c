#include "get_next_line.h"

int main() {
    int fd = open("hello.txt", O_RDONLY);
	char *line;

	line = get_next_line(fd);
	fprintf(stderr, "DEBUGPRINT[3]: test.c:8: line=%s\n", line);
	line = get_next_line(fd);
	fprintf(stderr, "DEBUGPRINT[4]: test.c:9: line=%s\n", line);
    close(fd);
    return 0;
}

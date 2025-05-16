#include "get_next_line.h"

int main() {
    int fd = open("hello.txt", O_RDONLY);
	char *line;

	printf("---------\n");
	line = get_next_line(fd);
	printf("line 1: %s\n", line);
	printf("---------\n");
	line = get_next_line(fd);
	printf("line 2: %s\n", line);
    close(fd);
    return 0;
}

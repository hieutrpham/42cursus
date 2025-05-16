#include "get_next_line.h"

int main() {
    int fd = open("hello.txt", O_RDONLY);
	char *line;

	for (int i = 0; i < 13; i++)
	{
		line = get_next_line(fd);
		printf("[%d]: %s\n", i, line);
	}
    close(fd);
    return 0;
}

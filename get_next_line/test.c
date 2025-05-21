#include "get_next_line.h"
#include <assert.h>
#include <string.h>

int main() {
    int fd = open("hello.txt", O_RDONLY);
    int fd1 = open("nl.txt", O_RDONLY);
    int fd2 = open("no_nl.txt", O_RDONLY);
	char *line;

	while((line = get_next_line(fd)))
	{
		fprintf(stderr, "DEBUGPRINT[4]: test.c:9: line=%s", line);
		fprintf(stderr, "DEBUGPRINT[4]: test.c:9: line=%d", ft_strlen(line));
	}
	// line = get_next_line(fd);
	// fprintf(stderr, "DEBUGPRINT[19]: test.c:14: line=%s\n", line);

    return 0;
}

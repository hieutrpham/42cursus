#include "get_next_line.h"
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	int		fd1;
	int		fd2;
	int		fd3;
	char	*line;

	fd = open("hello.txt", O_RDONLY);
	fd1 = open("gnlTester/files/empty", O_RDONLY);
	fd2 = open("gnlTester/files/41_no_nl", O_RDONLY);
	fd3 = open("gnlTester/files/42_with_nl", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		fprintf(stderr, "DEBUGPRINT[4]: test.c:9: line=%s", line);
		free(line);
	}
	// line = get_next_line(fd);
	// fprintf(stderr, "DEBUGPRINT[19]: test.c:14: line=%s\n", line);
	return (0);
}

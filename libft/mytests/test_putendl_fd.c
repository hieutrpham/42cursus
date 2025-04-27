#include "test.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int test_putendl_fd()
{
	TITLE("ft_putendl_fd");
	int test_count = 0;
	int test_failures = 0;
	{
		char output[100] = {0};
		int fd = open("tmp", O_RDWR | O_CREAT, 0777);
		ft_putendl_fd("hello", fd);
		lseek(fd, 0, SEEK_SET);
		read(fd, output, strlen("hello\n"));
		TEST(strcmp(output, "hello\n")==0);
		unlink("tmp");
		close(fd);
	}
	return test_failures;
}

#include "test.h"

int test_putstr_fd()
{
	int test_count = 0;
	int test_failures = 0;
	TITLE("ft_putstr_fd");
	{
		char output[100] = {0};
		int fd = open("temp", O_RDWR | O_CREAT, 0777);
		ft_putstr_fd("hello", fd); 
		lseek(fd, 0, SEEK_SET);
		read(fd, output, strlen("hello"));
		TEST(strcmp(output, "hello") == 0);
		unlink("temp");
		close(fd);
	}
	return test_failures;
}

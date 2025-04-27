#include "test.h"

int test_putnbr_fd()
{
	TITLE("ft_putnbr_fd");
	int test_count = 0;
	int test_failures = 0;
	char output[100] = {0};
	int fd = open("temp", O_RDWR | O_CREAT, 0777);
	ft_putnbr_fd(-12345, fd);
	lseek(fd, 0, SEEK_SET);
	read(fd, output, strlen("-12345"));
	TEST(strcmp(output, "-12345") == 0);
	unlink("temp");
	close(fd);
	return test_failures;
}

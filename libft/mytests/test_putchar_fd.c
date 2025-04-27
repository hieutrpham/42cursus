#include "test.h"
int test_putchar_fd()
{
	int test_count = 0;
	int test_failures = 0;
	TITLE("ft_putchar_fd");
	char output[100] = {0};
	int fd = open("temp", O_RDWR | O_CREAT, 0777);
	ft_putchar_fd('4', fd);
	ft_putchar_fd('2', fd);
	lseek(fd, 0, SEEK_SET);
	read(fd, output, 2);
	/*1*/TEST(strcmp(output, "42") == 0);
	unlink("temp");
	close(fd);
	return test_failures;
}

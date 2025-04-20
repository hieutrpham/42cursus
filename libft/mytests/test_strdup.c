#include "test.h"

int test_strdup()
{
	int test_count = 0;
	int test_failures = 0;
	TITLE("ft_strdup");
	char *str = ft_strdup("hello");
	/*1*/ TEST(strcmp(str, "hello") == 0);
	free(str);
	str = ft_strdup("");
	/*1*/ TEST(strcmp(str, "") == 0);
	free(str);
	return test_failures;
}

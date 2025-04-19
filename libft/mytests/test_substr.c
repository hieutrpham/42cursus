#include "test.h"
#include <string.h>

int test_substr()
{
	TITLE("ft_substr");
	int test_count = 0;
	int test_failures = 0;
	const char *str = "helloworld";
	
	/*1*/ TEST(strcmp(ft_substr(str, 2, 5), "llowo") == 0);
	/*2*/ TEST(strcmp(ft_substr(str, 2, 7), "lloworl") == 0);
	/*3*/ TEST(ft_substr(str, 299, 5) == NULL);
	/*4*/ TEST(ft_substr(str, 2, 19) == NULL);
	/*5*/ TEST(strcmp(ft_substr(str, 0, 5), "hello") == 0);
	return test_failures;
}

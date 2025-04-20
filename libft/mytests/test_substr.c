#include "test.h"
#include <string.h>

int test_substr()
{
	TITLE("ft_substr");
	int test_count = 0;
	int test_failures = 0;
	const char *str = "helloworld";
	char *s;	

	/*1*/ TEST(strcmp(ft_substr(str, 0, 42000), "helloworld") == 0);
	/*2*/ TEST(strcmp(ft_substr(str, 2, 7), "lloworl") == 0);
	/*3*/ TEST(!!ft_substr(str, 299, 5));
	/*4*/ TEST(!!ft_substr(str, 100, 1));
	/*5*/ TEST(strcmp(ft_substr(str, 0, 5), "hello") == 0);
	str = strdup("0123456789");
	s = ft_substr(str, 9, 10);
	/*6*/ TEST(!strcmp(s, "9"));

	return test_failures;
}

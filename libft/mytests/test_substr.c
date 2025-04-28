#include "test.h"
#include <string.h>

int test_substr()
{
	TITLE("ft_substr");
	int test_count = 0;
	int test_failures = 0;
	char *str = "helloworld";
	char *s;

	s = ft_substr(str, 0, 42000);
	/*1*/ TEST(strcmp(s, "helloworld") == 0);
	free(s);
	s = ft_substr(str, 2, 7);
	/*2*/ TEST(strcmp(s, "lloworl") == 0);
	free(s);
	s = ft_substr(str, 299, 5);
	/*3*/ TEST(!!s);
	free(s);
	s = ft_substr(str, 0, 5);
	/*4*/ TEST(strcmp(s, "hello") == 0);
	free(s);
	str = strdup("0123456789");
	s = ft_substr(str, 9, 10);
	/*5*/ TEST(!strcmp(s, "9"));
	/*6*/ TEST(strlen(s) == 1);
	free(str);
	free(s);
	str = NULL;
	s = ft_substr(str, 1, 2);
	/*7*/TEST(s == NULL);

	return test_failures;
}

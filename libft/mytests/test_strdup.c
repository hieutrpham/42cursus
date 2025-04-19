#include "test.h"

int test_strdup()
{
	int test_count = 0;
	int test_failures = 0;
	TITLE("ft_strdup");
	/*1*/ TEST(strcmp(ft_strdup("hello"), strdup("hello")) == 0);
	/*2*/ TEST(strcmp(ft_strdup("isdjf34"), strdup("isdjf34")) == 0);
	/*3*/ TEST(strcmp(ft_strdup(""), strdup("")) == 0);
	return test_failures;
}

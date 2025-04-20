#include "test.h"

int test_strjoin()
{
	TITLE("ft_strjoin");
	int test_count = 0;
	int test_failures = 0;
	/*1*/TEST(!strcmp(ft_strjoin("hello", "world"), "helloworld"));
	/*2*/TEST(!strcmp(ft_strjoin("", ""), ""));
	/*3*/TEST(!strcmp(ft_strjoin("", "world"), "world"));
	/*4*/TEST(!strcmp(ft_strjoin("hello", ""), "hello"));

	return test_failures;
}

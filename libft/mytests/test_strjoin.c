#include "test.h"

int test_strjoin()
{
	TITLE("ft_strjoin");
	int test_count = 0;
	int test_failures = 0;
	char *s = ft_strjoin("hello", "world");
	/*1*/TEST(!strcmp(s, "helloworld"));
	free(s);
	s = ft_strjoin("", "");
	/*2*/TEST(!strcmp(s, ""));
	free(s);
	s = ft_strjoin("", "world");
	/*3*/TEST(!strcmp(s, "world"));
	free(s);
	s = ft_strjoin("hello", "");
	/*4*/TEST(!strcmp(s, "hello"));
	free(s);

	return test_failures;
}

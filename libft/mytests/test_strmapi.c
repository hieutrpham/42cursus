#include "test.h"

char f(unsigned int i, char c) 
{
	(void) i;
	return ft_toupper(c);
}
int test_strmapi()
{
	int test_count = 0;
	int test_failures = 0;
	char *str;
	TITLE("ft_strmapi");
	/*1*/ TEST(!strcmp(str = ft_strmapi("hello", f), "HELLO"));
	free(str);
	/*2*/ TEST(!strcmp(str = ft_strmapi("", f), ""));
	free(str);
	return test_failures;
}

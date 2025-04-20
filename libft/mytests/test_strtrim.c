#include "test.h"
#include <string.h>

int test_strtrim()
{
	TITLE("ft_strtrim");
	int test_count = 0;
	int test_failures = 0;
	char *str;

	str = ft_strtrim("ababaaaMy name is Hieubbaaabbab", "ab");
	/*1*/TEST(!strcmp(str, "My name is Hieu"));
	/*1*/TEST(!strcmp(str, "hieu"));
	/*1*/TEST(!strcmp(str, "hieu"));
	free(str);
	return test_failures;
}

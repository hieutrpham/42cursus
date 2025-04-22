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
	free(str);
	str = ft_strtrim("aaxxxxxxhieu", "ax");
	/*2*/TEST(!strcmp(str, "hieu"));
	free(str);
	str = ft_strtrim("hieuaaaxxxx", "xa");
	/*3*/TEST(!strcmp(str, "hieu"));
	free(str);
	str = ft_strtrim(" xxxx xxx  ", "x ");
	/*4*/TEST(!strcmp(str, ""));
	free(str);
	str = ft_strtrim("abcdba", "acb");
	/*5*/TEST(!strcmp(str, "d"));
	free(str);
	str = ft_strtrim("--------", "-");
	/*6*/TEST(!strcmp(str, ""));
	free(str);
	return test_failures;
}

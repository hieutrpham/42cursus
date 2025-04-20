#include "test.h"

int test_calloc()
{
	int test_count = 0;
	int test_failures = 0;
	TITLE("ft_calloc");
	char *s = ft_calloc(4, 4);
	char *s1 = calloc(4,4);
	/*1*/TEST(!memcmp(s, s1, 16));
	free(s);
	free(s1);
	return test_failures;
}

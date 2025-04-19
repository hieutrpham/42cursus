#include "test.h"

int test_calloc()
{
	int test_count = 0;
	int test_failures = 0;
	TITLE("ft_calloc");
	/*1*/TEST(!memcmp(ft_calloc(4, 4), calloc(4, 4), 16));
	/*2*/TEST(!memcmp(ft_calloc(1, 2), calloc(1, 2), 2));
	/*3*/TEST(!memcmp(ft_calloc(9, 4), calloc(9, 4), 9*4));
	return test_failures;
}

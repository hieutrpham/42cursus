#include "test.h"

int test_itoa()
{
	TITLE("ft_itoa");
	int test_count = 0;
	int test_failures = 0;
	char *str;
	/*1*/TEST(!strcmp(str = ft_itoa(123), "123"));
	free(str);
	/*2*/TEST(!strcmp(str = ft_itoa(-12), "-12"));
	free(str);
	/*3*/TEST(!strcmp(str = ft_itoa(INT_MAX), "2147483647"));
	free(str);
	/*4*/TEST(!strcmp(str = ft_itoa(INT_MIN), "-2147483648"));
	free(str);
	/*5*/TEST(!strcmp(str = ft_itoa(0), "0"));
	free(str);
	return test_failures;
}

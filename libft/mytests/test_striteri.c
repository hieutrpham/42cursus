#include "test.h"

static void f(unsigned int i, char *c) 
{
	(void) i;
		*c = *c + i;
}
int test_striteri()
{
	int test_count = 0;
	int test_failures = 0;
	char str[] = "0000";
	TITLE("ft_striteri");
	ft_striteri(str, f);
	/*1*/ TEST(!strcmp(str, "0123"));
	{char str[] = "";
	ft_striteri(str, f);
	/*2*/ TEST(!strcmp(str, ""));
	}
	return test_failures;
}

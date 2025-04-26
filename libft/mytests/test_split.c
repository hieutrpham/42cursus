#include "test.h"

static void ft_free(char **arr)
{
	int i = 0;

	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
int test_split()
{
	TITLE("ft_split");
	int test_count = 0;
	int test_failures = 0;
	char **arr;

	arr = ft_split("hello,world", ',');
	/*1*/TEST(!strcmp(arr[0], "hello"));
	/*2*/TEST(!strcmp(arr[1], "world"));
	ft_free(arr);
	arr = ft_split(",,,hello,world,hi,mom", ',');
	/*3*/TEST(!strcmp(arr[0], "hello"));
	/*4*/TEST(!strcmp(arr[1], "world"));
	ft_free(arr);
	arr = ft_split("", ',');
	/*5*/TEST(arr[0] == NULL);
	ft_free(arr);
	arr = ft_split("mom", 0);
	/*6*/TEST(!strcmp(arr[0], "mom"));
	/*7*/TEST(arr[1] == NULL);
	ft_free(arr);
	arr = ft_split("      ", ' ');
	/*8*/TEST(arr[0] == NULL);
	ft_free(arr);
	arr = ft_split("  x   ", ' ');
	/*9*/TEST(!strcmp(arr[0], "x"));
	ft_free(arr);
	arr = ft_split(NULL, ' ');
	/*10*/TEST(arr == NULL);
	return test_failures;
}

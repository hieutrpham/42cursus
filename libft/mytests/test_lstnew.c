#include "test.h"

int test_lstnew()
{
	int test_count = 0;
	int test_failures = 0;
	TITLE("ft_lstnew");
	t_list *node = ft_lstnew((void*)42);
	/*1*/TEST(node != NULL);
	/*2*/TEST(node->content == (void*)42);
	/*3*/TEST(node->next == NULL);
	return test_failures;
}

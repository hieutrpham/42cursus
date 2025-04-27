#include "test.h"

int test_lstsize()
{
	int test_count = 0;
	int test_failures = 0;
	TITLE("ft_lstsize");
	t_list *list = NULL;
	/*1*/TEST(ft_lstsize(list) == 0);
	ft_lstadd_front(&list, ft_lstnew((void*) 3));
	/*2*/TEST(ft_lstsize(list) == 1);
	ft_lstadd_front(&list, ft_lstnew((void*) 2));
	/*3*/TEST(ft_lstsize(list) == 2);
	ft_lstadd_front(&list, ft_lstnew((void*) 1));
	/*4*/TEST(ft_lstsize(list) == 3);;
	ft_lstclear(&list, free);
	return test_failures;
}


#include "test.h"

int test_lstadd_front()
{
	int test_count = 0;
	int test_failures = 0;
	TITLE("ft_lstadd_front");
	t_list *node = NULL;
	ft_lstadd_front(&node, ft_lstnew((void*)1));
	ft_lstadd_front(&node, ft_lstnew((void*)2));
	ft_lstadd_front(&node, ft_lstnew((void*)3));
	/*1*/TEST(node->content == (void*)3);
	/*2*/TEST(node->next->content == (void*)2);
	/*3*/TEST(node->next->next->content == (void*)1);
	ft_lstclear(&node, free);
	return test_failures;
}


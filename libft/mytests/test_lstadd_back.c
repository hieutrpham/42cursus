#include "test.h"

int test_lstadd_back()
{
	int test_count = 0;
	int test_failures = 0;
	TITLE("ft_lstadd_back");
	t_list *list = NULL;
	ft_lstadd_back(&list, ft_lstnew((void*) 1));
	ft_lstadd_back(&list, ft_lstnew((void*) 2));
	ft_lstadd_back(&list, ft_lstnew((void*) 3));
	TEST(list->content == (void*) 1);
	TEST(list->next->content == (void*) 2);
	TEST(list->next->next->content == (void*) 3);
	ft_lstclear(&list, free);
	return test_failures;
}


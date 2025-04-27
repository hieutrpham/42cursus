#include "test.h"

int test_lstclear()
{
	int test_count = 0;
	int test_failures = 0;
	TITLE("ft_lstclear");
	t_list *list = NULL;
	ft_lstadd_back(&list, ft_lstnew((void*)1));
	ft_lstadd_back(&list, ft_lstnew((void*)2));
	ft_lstadd_back(&list, ft_lstnew((void*)3));
	ft_lstclear(&list, free);
	TEST(list == NULL);
	return test_failures;
}


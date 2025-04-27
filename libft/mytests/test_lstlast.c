#include "test.h"

int test_lstlast()
{
	int test_count = 0;
	int test_failures = 0;
	TITLE("ft_lstlast");
	t_list *list = NULL;
	TEST(ft_lstlast(list) == NULL);
	ft_lstadd_front(&list, ft_lstnew((void*) 3));
	ft_lstadd_front(&list, ft_lstnew((void*) 2));
	ft_lstadd_front(&list, ft_lstnew((void*) 1));
	TEST(ft_lstlast(list)->content == (void*) 3);
	ft_lstclear(&list, free);
	return test_failures;
}


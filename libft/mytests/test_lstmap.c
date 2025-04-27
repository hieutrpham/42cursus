#include "test.h"

static void increment_int(void *ptr)
{
	*(int*)ptr += 1;
}
int test_lstmap()
{
	int test_count = 0;
	int test_failures = 0;
	TITLE("ft_lstmap");
	int nodes_visited = 0;
	t_list *list = NULL;
	ft_lstadd_back(&list, ft_lstnew(&nodes_visited));
	ft_lstadd_back(&list, ft_lstnew(&nodes_visited));
	ft_lstadd_back(&list, ft_lstnew(&nodes_visited));
	ft_lstiter(list, increment_int);
	TEST(nodes_visited == 3);
	ft_lstclear(&list, free);
	return test_failures;
}


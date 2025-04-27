#include "test.h"
void *addOne(void *p) 
{
	void *r = malloc(sizeof(int)); 
	*(int*)r = *(int*)p + 1;
	return (r);
}

int test_lstmap()
{
	int test_count = 0;
	int test_failures = 0;
	TITLE("ft_lstmap");
	int tab[] = {0, 1, 2, 3};
	t_list * l =  ft_lstnew(tab);
	for (int i = 1; i < 4; ++i)
		ft_lstadd_back(&l, ft_lstnew(tab + i));
	t_list * m = ft_lstmap(l, addOne, free);
	t_list * tmp = l;
	/* 1 2 3 4 */ for (int i = 0; i < 4; ++i)
	{
		TEST(*(int*)tmp->content == i);
		tmp = (t_list *)tmp->next;
	}
	ft_lstclear(&l, free);
	return test_failures;
}


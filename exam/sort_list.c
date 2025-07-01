#include <stdlib.h>

typedef struct s_list {
	int data;
	struct s_list *next;
} t_list;

t_list *sort_list(t_list *lst, int (*cmp)(int, int))
{
	t_list *head;

	head = lst;
	while (lst != NULL && lst->next != NULL)
	{
		if (cmp(lst->data, lst->next->data) == 0)
		{
			int tmp = lst->data;
			lst->data = lst->next->data;
			lst->next->data = tmp;
			lst = head;
		}
		else
			lst = lst->next;
	}
	return head;
}

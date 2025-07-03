#include <stdlib.h>

typedef struct s_list {
	int data;
	struct s_list *next;
} t_list;

t_list *sort_list1(t_list *lst, int (*cmp)(int, int))
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

// i did this in exam
int issorted(t_list *lst, int* cmp(int, int))
{
	while (lst)
	{
		if (cmp(lst->data, lst->next->data) == 0)
			return 0;
		lst = lst->next;
	}
	return 1;
}

t_list *sort_list(t_list *lst, int *cmp(int, int))
{
	t_list *curr;

	curr = lst;
	while (!issorted(lst, cmp))
	{
		curr = lst;
		while (curr && curr->next)
		{
			if (cmp(curr->data, curr->next->data) == 0)
			{
				int tmp = curr->data;
				curr->data = curr->next->data;
				curr->next->data = tmp;
			}
			curr = curr->next;
		}
	}
	return lst;
}

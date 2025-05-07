#include "ft_printf.h"

int main()
{
	int count = ft_printf("newtest %c %s", 'u', "helloworld");
	printf("%d\n", count);
	return 0;
}

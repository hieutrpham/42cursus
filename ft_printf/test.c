#include "ft_printf.h"

int main()
{
	// int p = 0;
	// int i = ft_printf("%p", &p);
	// printf("\n%d", i);
	int i = ft_printf("%X %x", 123143, 42);
	printf("\n");
	printf("ft_printf: %d\n", i);
	printf("\n");
	printf("printf: %d\n", printf("%X %x", 123143, 42));
	// char hexdigits[] = "0123456789abdcef";
	// ft_putchar(hexdigits[15 % 16]);
	return 0;
}

#include "ft_printf.h"
#include <stdio.h>
int	main(void)
{
	int i = ft_printf(" %x ", 16);
	printf("\n%d\n", i);
	int j = printf(" %x ", 16);
	printf("\n%d\n", j);
	// int i = ft_printf("%X %x", 123143, 42);
	// printf("\n");
	// printf("ft_printf: %d\n", i);
	// printf("\n");
	// printf("printf: %d\n", printf("%X %x", 123143, 42));
	// char hexdigits[] = "0123456789abdcef";
	// ft_putchar(hexdigits[15 % 16]);
	return (0);
}

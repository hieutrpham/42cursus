#include "ft_printf.h"
#include <stdio.h>
int	main(void)
{
	int	p;

	p = 0;
	ft_printf("ft: %p", &p);
	printf("\nprintf: %p", &p);
	// printf("%d", i);
	// int i = ft_printf("%X %x", 123143, 42);
	// printf("\n");
	// printf("ft_printf: %d\n", i);
	// printf("\n");
	// printf("printf: %d\n", printf("%X %x", 123143, 42));
	// char hexdigits[] = "0123456789abdcef";
	// ft_putchar(hexdigits[15 % 16]);
	return (0);
}

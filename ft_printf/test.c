#include "ft_printf.h"
#include <stdio.h>
int	main(void)
{
    close(1);

    // Call ft_printf, which should now fail to write
    int ret = ft_printf("Hello, world!\n");

    // Print the result to stderr
    if (ret == -1) {
        fprintf(stderr, "ft_printf returned -1 on write error as expected.\n");
    } else {
        fprintf(stderr, "ft_printf did NOT return -1 (returned %d).\n", ret);
    }
	// int i = ft_printf("%X %x", 123143, 42);
	// printf("\n");
	// printf("ft_printf: %d\n", i);
	// printf("\n");
	// printf("printf: %d\n", printf("%X %x", 123143, 42));
	// char hexdigits[] = "0123456789abdcef";
	// ft_putchar(hexdigits[15 % 16]);
	return (0);
}

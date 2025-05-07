#include "ft_printf.h"

int main()
{
	int i = ft_printf("why %d %i", -123, 8239848);
	printf("\n%d", i);
	// printf("\n%d\n", ft_putnbr(-2312323));
	return 0;
}

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	if (n == 0 || size == 0)
		return (malloc(0));
	ptr = malloc(n * size);
	if (!ptr)
		return (NULL);
	while (i < n * size)
		ptr[i++] = 0;
	return (ptr);
}

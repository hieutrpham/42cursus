#include "test.h"
#include "../libft.h"

int test_memcpy() {
    int test_failures = 0;
	int test_count = 0;
	TITLE("ft_memcpy");

    char src[] = "Hello, World!";
    char dst1[20] = {0};
    char dst2[20] = {0};

    /* 1 */TEST(ft_memcpy(dst1, src, strlen(src) + 1) == dst1);  // Check return value
    /* 2 */TEST(ft_memcpy(dst1, src, strlen(src) + 1) == memcpy(dst1, src, strlen(src) + 1));  // Check return value
    /* 3 */TEST(strcmp(dst1, src) == 0);                         // Check full copy
    /* 4 */TEST(ft_memcpy(dst2, src, 5) == dst2);
    dst2[5] = '\0';
    /* 5 */TEST(strcmp(dst2, "Hello") == 0);                     // Check partial copy

    // Overlapping (undefined behavior, but shouldn't crash)
    char buf[] = "abcdef";
    ft_memcpy(buf + 2, buf, 3);

    return test_failures;
}

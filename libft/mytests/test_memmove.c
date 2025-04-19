#include "../libft.h"
#include "test.h"

int test_memmove() {
    TITLE("ft_memmove");
    char src[] = "Hello, World!";
    char dst1[20] = {0};
    char dst2[20] = {0};
    int test_count =0;
    int test_failures = 0;
    // Test basic copy (same as memcpy)
    ft_memmove(dst1, src, strlen(src) + 1);
/* 1 */TEST(strcmp(dst1, src) == 0);

    // Test partial copy
    ft_memmove(dst2, src, 5);
    dst2[5] = '\0';
/* 2 */TEST(strcmp(dst2, "Hello") == 0);

    // Test overlapping (src < dst)
    char buf1[] = "abcdef";
    ft_memmove(buf1 + 2, buf1, 3);
/* 3 */   TEST(strcmp(buf1, "ababcf") == 0);

    // Test overlapping (src > dst)
    char buf2[] = "abcdef";
    ft_memmove(buf2, buf2 + 2, 3);
/* 4 */   TEST(strcmp(buf2, "cdedef") == 0);
    return 0;
}

#include "test.h"

int test_strlcat(void)
{
    TITLE("ft_strlcat");
    int test_count = 0;
    int test_failures = 0;
    
    char dst1[20] = "hello";
    char dst2[20] = "hello";
    char src[] = " world";
    
    /* 1 */ TEST(ft_strlcat(dst1, src, 20) == strlcat(dst2, src, 20));
    /* 2 */ TEST(strcmp(dst1, dst2) == 0);
    /* 3 */ TEST(ft_strlcat(dst1, src, 5) == strlcat(dst2, src, 5));
    /* 4 */ TEST(ft_strlcat(dst1, src, -5) == strlcat(dst2, src, -5));
    
    return test_failures;
}

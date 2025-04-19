#include "test.h"

int test_strlcpy(void)
{
    TITLE("ft_strlcpy");
    int test_count = 0;
    int test_failures = 0;
    
    char dst1[10];
    char dst2[10];
    char src[] = "hello";
    
    /* 1 */ TEST(ft_strlcpy(dst1, src, 10) == strlcpy(dst2, src, 10));
    /* 2 */ TEST(strcmp(dst1, dst2) == 0);
    /* 3 */ TEST(ft_strlcpy(dst1, src, 3) == strlcpy(dst2, src, 3));
    
    return test_failures;
}

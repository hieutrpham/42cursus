#include "test.h"
int test_bzero(void)
{
    TITLE("ft_bzero");
    int test_count = 0;
    int test_failures = 0;
    
    char str1[10] = "hello";
    char str2[10] = "hello";
    
    /* 1 */ ft_bzero(str1, 3); bzero(str2, 3);
    TEST(memcmp(str1, str2, 10) == 0);
    
    /* 2 */ ft_bzero(str1, 0); bzero(str2, 0);
    TEST(memcmp(str1, str2, 10) == 0);
    
    /* 3 */ ft_bzero(str1, 10); bzero(str2, 10);
    TEST(memcmp(str1, str2, 10) == 0);
    
    return test_failures;
}

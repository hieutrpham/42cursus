#include "test.h"

int test_memcmp(void)
{
    TITLE("ft_memcmp");
    int test_count = 0;
    int test_failures = 0;
    
    char s1[] = "abcde";
    char s2[] = "abcdf";
    
    /* 1 */ TEST(ft_memcmp(s1, s2, 4) == memcmp(s1, s2, 4));
    /* 2 */ TEST(ft_memcmp(s1, s2, 5) == memcmp(s1, s2, 5));
    /* 3 */ TEST(ft_memcmp(s1, s1, 5) == memcmp(s1, s1, 5));
    
    return test_failures;
}

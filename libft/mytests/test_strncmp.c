#include "test.h"

int test_strncmp(void)
{
    TITLE("ft_strncmp");
    int test_count = 0;
    int test_failures = 0;
    
    char s1[] = "abcde";
    char s2[] = "abcdf";
    
    /* 1 */ TEST(ft_strncmp(s1, s2, 4) == strncmp(s1, s2, 4));
    /* 2 */ TEST(ft_strncmp(s1, s2, 5) == strncmp(s1, s2, 5));
    /* 3 */ TEST(ft_strncmp(s1, s1, 5) == strncmp(s1, s1, 5));
    /* 4 */ TEST(!!ft_strncmp("abc\200", "abc\0", 6) == !!strncmp("abc\200", "abc\0", 6));
    /* 5 */ TEST(!!ft_strncmp("eirej", "e", 42) == !!strncmp("eirej", "e", 42));
    
    return test_failures;
}

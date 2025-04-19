#include "test.h"

int test_memchr(void)
{
    TITLE("ft_memchr");
    int test_count = 0;
    int test_failures = 0;
    
    char str[] = "Hello world";
    
    /* 1 */ TEST(ft_memchr(str, 'o', 11) == memchr(str, 'o', 11));
    /* 2 */ TEST(ft_memchr(str, 'z', 11) == memchr(str, 'z', 11));
    /* 3 */ TEST(ft_memchr(str, '\0', 12) == memchr(str, '\0', 12));
    
    return test_failures;
}

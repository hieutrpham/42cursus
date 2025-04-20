#include "test.h"

int test_memset(void)
{
    TITLE("ft_memset");
    int test_count = 0;
    int test_failures = 0;
    
    char buf1[10] = {0};
    // char buf2[10];
    
    /* 1 */ TEST(memcmp(ft_memset(buf1, 'x', 5), memset(buf1, 'x', 5), 10) == 0);
    /* 2 */ TEST(ft_memset(buf1, 0, 10) == buf1);
    
    return test_failures;
}

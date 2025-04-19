#include "test.h"

int test_isascii(void)
{
    TITLE("ft_isascii");
    int test_count = 0;
    int test_failures = 0;
    
    /* 1 */ TEST(ft_isascii(0) == isascii(0));
    /* 2 */ TEST(ft_isascii(127) == isascii(127));
    /* 3 */ TEST(ft_isascii(128) == isascii(128));
    /* 4 */ TEST(ft_isascii(-1) == isascii(-1));
    
    return test_failures;
}

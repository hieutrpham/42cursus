#include "test.h"

int test_isprint(void)
{
    TITLE("ft_isprint");
    int test_count = 0;
    int test_failures = 0;
    
    /* 1 */ TEST(ft_isprint(' ') == isprint(' '));
    /* 2 */ TEST(ft_isprint('~') == isprint('~'));
    /* 3 */ TEST(ft_isprint(31) == isprint(31));
    /* 4 */ TEST(ft_isprint(127) == isprint(127));
    
    return test_failures;
}

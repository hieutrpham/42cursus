#include "test.h"

int test_isdigit(void)
{
    TITLE("ft_isdigit");
    int test_count = 0;
    int test_failures = 0;
    
    /* 1 */ TEST(ft_isdigit('0') == isdigit('0'));
    /* 2 */ TEST(ft_isdigit('9') == isdigit('9'));
    /* 3 */ TEST(ft_isdigit('A') == isdigit('A'));
    /* 4 */ TEST(ft_isdigit('@') == isdigit('@'));
    
    return test_failures;
}

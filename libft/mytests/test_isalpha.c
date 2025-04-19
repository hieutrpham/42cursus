#include "test.h"

int test_isalpha(void)
{
    TITLE("ft_isalpha");
    int test_count = 0;
    int test_failures = 0;
    
    /* 1 */ TEST(!!ft_isalpha('A') == !!isalpha('A'));
    /* 2 */ TEST(!!ft_isalpha('z') == !!isalpha('z'));
    /* 3 */ TEST(!!ft_isalpha('0') == !!isalpha('0'));
    /* 4 */ TEST(!!ft_isalpha('@') == !!isalpha('@'));
    
    return test_failures;
}

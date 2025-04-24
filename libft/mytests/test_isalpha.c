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
    /* 5 */ TEST(!!ft_isalpha(-1) == !!isalpha(-1));
    /* 6 */ TEST(!!ft_isalpha('a' + 256) == !!isalpha('a' + 256));
    
    return test_failures;
}

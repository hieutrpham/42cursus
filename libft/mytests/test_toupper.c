#include "test.h"
int test_toupper(void)
{
    TITLE("ft_toupper");
    int test_count = 0;
    int test_failures = 0;
    
    /* 1 */ TEST(ft_toupper('a') == toupper('a'));
    /* 2 */ TEST(ft_toupper('z') == toupper('z'));
    /* 3 */ TEST(ft_toupper('A') == toupper('A'));
    /* 4 */ TEST(ft_toupper('1') == toupper('1'));
    /* 5 */ TEST(ft_toupper('@') == toupper('@'));
    
    return test_failures;
}

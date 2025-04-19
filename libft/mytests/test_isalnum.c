#include "test.h"
int test_isalnum(void)
{
    TITLE("ft_isalnum");
    int test_count = 0;
    int test_failures = 0;
    
    /* 1 */ TEST(ft_isalnum('a') == isalnum('a'));
    /* 2 */ TEST(ft_isalnum('Z') == isalnum('Z'));
    /* 3 */ TEST(ft_isalnum('1') == isalnum('1'));
    /* 4 */ TEST(ft_isalnum('@') == isalnum('@'));
    /* 5 */ TEST(ft_isalnum(0) == isalnum(0));
    
    return test_failures;
}

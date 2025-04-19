#include "test.h"

int test_atoi(void)
{
    TITLE("ft_atoi");
    int test_count = 0;
    int test_failures = 0;
    
    /* 1 */ TEST(ft_atoi("-42") == atoi("-42"));
    /* 2 */ TEST(ft_atoi("0") == atoi("0"));
    /* 3 */ TEST(ft_atoi("2147483647") == atoi("2147483647"));
    /* 4 */ TEST(ft_atoi("-2147483648") == atoi("-2147483648"));
    /* 5 */ TEST(ft_atoi("  +123") == atoi("  +123"));
    /* 6 */ TEST(ft_atoi("invalid") == atoi("invalid"));
    
    return test_failures;
}

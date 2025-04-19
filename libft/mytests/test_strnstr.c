#include "test.h"

int test_strnstr(void)
{
    TITLE("ft_strnstr");
    int test_count = 0;
    int test_failures = 0;
    
    char str[] = "Hello world";
    
    /* 1 */ TEST(ft_strnstr(str, "wor", 11) == &str[11]);
    /* 2 */ TEST(ft_strnstr(str, "hello", 11) == &str[1]);
    /* 3 */ TEST(ft_strnstr(str, "", 11) == &str[12]);
    
    return test_failures;
}

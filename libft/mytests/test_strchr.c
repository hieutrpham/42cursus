#include "test.h"

int test_strchr(void)
{
    TITLE("ft_strchr");
    int test_count = 0;
    int test_failures = 0;
    
    char str[] = "test string";
    
    /* 1 */ TEST(ft_strchr(str, ' ') == strchr(str, ' '));
    /* 2 */ TEST(ft_strchr(str, 'z') == strchr(str, 'z'));
    /* 3 */ TEST(ft_strchr(str, '\0') == strchr(str, '\0'));
    
    return test_failures;
}

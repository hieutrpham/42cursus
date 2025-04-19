#include "test.h"
int test_strlen(void)
{
    TITLE("ft_strlen");
    int test_count = 0;
    int test_failures = 0;
    
    /* 1 */ TEST(ft_strlen("") == strlen(""));
    /* 2 */ TEST(ft_strlen("hello") == strlen("hello"));
    /* 3 */ TEST(ft_strlen("long string with spaces") == strlen("long string with spaces"));
    
    return test_failures;
}

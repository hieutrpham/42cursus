#include "test.h"

int test_tolower(void)
{
    TITLE("ft_tolower");
    int test_count = 0;
    int test_failures = 0;
    
    /* 1 */ TEST(ft_tolower('A') == tolower('A'));
    /* 2 */ TEST(ft_tolower('Z') == tolower('Z'));
    /* 3 */ TEST(ft_tolower('a') == tolower('a'));
    /* 4 */ TEST(ft_tolower('1') == tolower('1'));
    /* 5 */ TEST(ft_tolower('a' + 256) == tolower('a' + 256));
    
    return test_failures;
}

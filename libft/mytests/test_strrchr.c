#include "test.h"

int test_strrchr(void)
{
    TITLE("ft_strrchr");
    int test_count = 0;
    int test_failures = 0;
    
    char str[] = "test string";
    
    /* 1 */ TEST(ft_strrchr(str, 't') == strrchr(str, 't'));
    /* 2 */ TEST(ft_strrchr(str, 'z') == strrchr(str, 'z'));
    /* 3 */ TEST(ft_strrchr(str, '\0') == strrchr(str, '\0'));
    /* 4 */ TEST(ft_strrchr(str, 's' + 256) == strrchr(str, 's' + 256));
    
    return test_failures;
}

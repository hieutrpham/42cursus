#include "test.h"

int test_strnstr(void)
{
    TITLE("ft_strnstr");
    int test_count = 0;
    int test_failures = 0;
    
    char str[] = "Hello world";
    
    /* 1 */ TEST(strcmp(ft_strnstr(str, "wor", 11), strnstr(str, "wor", 11)) == 0);
    /* 2 */ TEST(strcmp(ft_strnstr(str, "He", 11), strnstr(str, "He", 11)) == 0);
    /* 3 */ TEST(strcmp(ft_strnstr(str, "o", 11), strnstr(str, "o", 11)) == 0);
    /* 4 */ TEST((ft_strnstr("", "o", 11) == strnstr("", "o", 11)));
    // /* 5 */ TEST((ft_strnstr(NULL, "o", 11) == strnstr(NULL, "o", 11)));
    
    return test_failures;
}

#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"

#define TEST(condition) do { \
    count++;  \
    if (!(condition)) {\
        printf(RED "%d.KO " RESET, count); \
        fail++;\
    } else {\
        printf(GREEN "%d.OK " RESET, count);\
    }\
} while (0)

#define COMPARE(format, ...) do { \
    char buffer1[1024] = {0}; \
    char buffer2[1024] = {0}; \
    int stdout_backup = dup(fileno(stdout)); \
    FILE *output1 = fmemopen(buffer1, sizeof(buffer1), "w"); \
    FILE *output2 = fmemopen(buffer2, sizeof(buffer2), "w"); \
    if (output1 == NULL || output2 == NULL) { \
        perror("Error opening buffer"); \
        exit(1); \
    } \
    dup2(fileno(output1), fileno(stdout)); \
    printf(YELLOW"printf: "RESET); \
    int ret1 = printf(format, __VA_ARGS__); \
    printf("\n"); \
    printf(YELLOW"ft_printf: "RESET); \
    fflush(stdout); \
    fclose(output1); \
\
    dup2(fileno(output2), fileno(stdout)); \
    int ret2 = ft_printf(format, __VA_ARGS__); \
    printf("\n"); \
    fflush(stdout); \
    fclose(output2); \
\
    dup2(stdout_backup, fileno(stdout)); \
    close(stdout_backup); \
    TEST(ret1 == ret2); \
    TEST(strcmp(buffer1, buffer2) == 0); \
    printf("\n"); \
} while (0)

int main(void)
{
    int count = 0;
    int fail = 0;
    int i = 0;
    char *str = NULL;
    /*1*/COMPARE("%d %i %p", -1, 32, &i);
    /*2*/COMPARE("%s", str);
    /*3*/COMPARE("null: %d %i %p %c", 123, -456, NULL, 'a'+256);
    /*4*/COMPARE("%d %i %p", -1, 32, &i);  // Testing integer and pointer
    /*5*/COMPARE("string: %s", "Hello, World!");  // Testing string
    /*6*/COMPARE("hex: %x %X %x", 0xff, -0xff, 0);      // Testing lowercase and uppercase hex
    /*7*/COMPARE("zero: %d", 0);                // Testing zero
    /*8*/COMPARE("pointer: %p", NULL);             // Testing null pointer
    /*9*/COMPARE("unsigned int: %u", 123456789);        // Testing unsigned integer
    /*10*/COMPARE("Test %%: %d%% of hivers are %s", 42, "weeps");        //testing %
    /*11*/COMPARE("INT_MIN INT_MAX: %d %i", INT_MIN, INT_MAX);
    /*12*/COMPARE("LONG_MIN LONG_MAX pointer: %p %p", (void*)LONG_MIN, (void*)LONG_MAX);
    /*13*/COMPARE("UINT_MAX hexadecimal: %x", UINT_MAX);
    /*14*/COMPARE("+ULONG_MAX pointer: %p", (void*) +ULONG_MAX);
    /*15*/COMPARE("-ULONG_MAX pointer: %p", (void*) -ULONG_MAX);
    // Test some invalid inputs that could cause segfault if not handled
    ft_printf(0);
    ft_printf(NULL);
    ft_printf("%q %", 123);
    ft_printf("%");
    // Final summary
    if (fail == 0)
        printf(GREEN "\nAll tests passed!" RESET);
    else
        printf(RED "\n%d tests failed." RESET, fail);

    return 0;
}

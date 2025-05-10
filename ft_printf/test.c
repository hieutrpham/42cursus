#include "ft_printf.h"
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

#define COMPARE_OUTPUT(format, ...) do { \
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
    printf(format, __VA_ARGS__); \
	printf("\n"); \
	printf(YELLOW"ft_printf: "RESET); \
    fflush(stdout); \
    fclose(output1); \
    dup2(fileno(output2), fileno(stdout)); \
    ft_printf(format, __VA_ARGS__); \
	printf("\n"); \
    fflush(stdout); \
    fclose(output2); \
    dup2(stdout_backup, fileno(stdout)); \
    close(stdout_backup); \
    TEST(strcmp(buffer1, buffer2) == 0); \
	printf("\n"); \
} while (0)

int main(void)
{
    int count = 0;
    int fail = 0;
    int i = 0;
	char *str = NULL;
    // Test basic format
    COMPARE_OUTPUT("%d %i %p", -1, 32, &i);
    COMPARE_OUTPUT("%s", str);

    // More tests can be added below:
    COMPARE_OUTPUT("%d %i %p %c", 123, -456, NULL, 'a'+256);
    COMPARE_OUTPUT("Hello, %s!", "world");
    COMPARE_OUTPUT("%x %X", 255, 255);		//testing hex
    COMPARE_OUTPUT("%d %i %p", -1, 32, &i);  // Testing integer and pointer
    COMPARE_OUTPUT("%s", "Hello, World!");  // Testing string
    COMPARE_OUTPUT("%x %X", 255, 255);      // Testing lowercase and uppercase hex
    COMPARE_OUTPUT("%d", 0);                // Testing zero
    COMPARE_OUTPUT("%p", NULL);             // Testing null pointer
    COMPARE_OUTPUT("%u", 123456789);        // Testing unsigned integer
    COMPARE_OUTPUT("%d%% of hivers are %s", 42, "weeps");        //testing %

    // Final summary
    if (fail == 0)
        printf(GREEN "\nAll tests passed!" RESET);
    else
        printf(RED "\n%d tests failed." RESET, fail);

    return 0;
}

#ifndef TEST_H
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libft.h"
#include "ctype.h"
#include <bsd/string.h>

// --- Colored output macros ---
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"

#define TITLE(title) do {\
    printf(YELLOW "\n%s:\t" RESET, title); \
} while (0)

#define TEST(condition) \
	do {\
	test_count++; \
	if (!(condition)) {\
		printf(RED "%d.KO " RESET, test_count); \
		 test_failures++;\
	} else {\
		printf(GREEN "%d.OK " RESET, test_count);\
	}\
	} while (0)

int test_atoi();
int test_bzero();
int test_isalnum();
int test_isalpha();
int test_isascii();
int test_isdigit();
int test_isprint();
int test_memchr();
int test_memcmp();
int test_memcpy();
int test_memmove();
int test_memset();
int test_strchr();
int test_strlcat();
int test_strlcpy();
int test_strlen();
int test_strncmp();
int test_strnstr();
int test_strrchr();
int test_tolower();
int test_toupper();
int test_calloc();
int test_strdup();
int test_substr();
int test_strjoin();
int test_strtrim();
int test_split();
int test_itoa();
int test_strmapi();
int test_striteri();
int test_putchar_fd();
int test_putstr_fd();
int test_putendl_fd();
int test_putnbr_fd();
#endif // !TEST_H

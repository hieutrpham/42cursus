/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:57:59 by trupham           #+#    #+#             */
/*   Updated: 2025/04/16 11:58:17 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_tmp;
	const unsigned char	*src_tmp;

	dest_tmp = dest;
	src_tmp = src;
	if (src >= dest)
		ft_memcpy(dest, src, n);
	else
	{
		while (n > 0)
		{
			*(dest_tmp + n - 1) = *(src_tmp + n - 1);
			n--;
		}
	}
	return (dest_tmp);
}
// #include <stdio.h>
// #include <string.h>
//
// // --- Colored output macros ---
// #define GREEN   "\033[32m"
// #define RED     "\033[31m"
// #define YELLOW  "\033[33m"
// #define RESET   "\033[0m"
//
// // --- Custom assertion macro (continues on failure) ---
// #define TEST(condition) \
//     do { \
//         if (!(condition)) { \
//             printf(RED "[FAIL]" RESET " %s:%d: %s\n", __FILE__, __LINE__, #condition); \
//             test_failures++; \
//         } else { \
//             printf(GREEN "[PASS]" RESET " %s\n", #condition); \
//         } \
//     } while (0)
// //
// // --- Test cases for ft_memmove ---
// int test_ft_memmove() {
//     int test_failures = 0;
//     printf(YELLOW "\n=== Testing ft_memmove ===\n" RESET);
//
//     char src[] = "Hello, World!";
//     char dst1[20] = {0};
//     char dst2[20] = {0};
//
//     TEST(ft_memmove(dst1, src, strlen(src) + 1) == dst1);
//     TEST(strcmp(dst1, src) == 0);                         // Normal copy
//
//     TEST(ft_memmove(dst2, src, 5) == dst2);
//     dst2[5] = '\0';
//     TEST(strcmp(dst2, "Hello") == 0);                     // Partial copy
//
//     // Overlapping (src < dst)
//     char buf1[] = "abcdef";
//     ft_memmove(buf1 + 2, buf1, 3);
//     TEST(strcmp(buf1, "ababcf") == 0);
//
//     // Overlapping (src > dst)
//     char buf2[] = "abcdef";
//     ft_memmove(buf2, buf2 + 2, 3);
//     TEST(strcmp(buf2, "cdedef") == 0);
//
//     return test_failures;
// }
// int main() {
//     int total_failures = 0;
//
//     total_failures += test_ft_memmove();
//
//     if (total_failures == 0) {
//         printf(GREEN "\nAll tests passed! 🎉\n" RESET);
//     } else {
//         printf(RED "\n%d tests failed! 💀\n" RESET, total_failures);
//     }
//
//     return (total_failures != 0);
// }
//

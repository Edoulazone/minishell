/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:56:43 by gnyssens          #+#    #+#             */
/*   Updated: 2024/04/17 13:34:30 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	unsigned char	*hay;
	unsigned char	*nee;
	size_t			i;
	size_t			j;

	if (*needle == '\0')
		return ((char *) haystack);
	hay = (unsigned char *)haystack;
	nee = (unsigned char *)needle;
	i = 0;
	while (hay[i] && i < n)
	{
		j = 0;
		while (nee[j] == hay[i + j] && i + j < n && nee[j] && hay[i + j])
			j++;
		if (nee[j] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (0);
}
/*
int main() {
    const char *haystack1 = "Hello World";
    const char *needle1 = "World";
    size_t n1 = 11; // Full length of haystack

    const char *haystack2 = "Hello World";
    const char *needle2 = "Wor";
    size_t n2 = 5; // Shorter than the occurrence of needle

    const char *haystack3 = "Hello World";
    const char *needle3 = "lo";
    size_t n3 = 5; // Exactly at the occurrence of needle

    const char *haystack4 = "Hello World";
    const char *needle4 = "!";
    size_t n4 = 11; // Needle not in haystack

    const char *haystack5 = "Hello World";
    const char *needle5 = "";
    size_t n5 = 11; // Empty needle

    char *result;

    result = ft_strnstr(haystack1, needle1, n1);
    printf("Result 1: %s\n", result ? result : "null");

    result = ft_strnstr(haystack2, needle2, n2);
    printf("Result 2: %s\n", result ? result : "null");

    result = ft_strnstr(haystack3, needle3, n3);
    printf("Result 3: %s\n", result ? result : "null");

    result = ft_strnstr(haystack4, needle4, n4);
    printf("Result 4: %s\n", result ? result : "null");

    result = ft_strnstr(haystack5, needle5, n5);
    printf("Result 5: %s\n", result ? result : "null");

    return 0;
}
*/

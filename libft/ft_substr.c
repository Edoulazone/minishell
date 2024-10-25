/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:48:48 by gnyssens          #+#    #+#             */
/*   Updated: 2024/04/17 13:26:27 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	alloc_len;
	size_t	i;
	char	*result;

	if (!s)
		return (0);
	alloc_len = len;
	if (ft_strlen(s) - start < len)
		alloc_len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	result = (char *)malloc(alloc_len + 1);
	if (!result)
		return (0);
	i = 0;
	while (i < alloc_len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

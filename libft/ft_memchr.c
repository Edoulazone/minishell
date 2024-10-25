/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:54:03 by gnyssens          #+#    #+#             */
/*   Updated: 2024/08/20 15:58:30 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*new_str;

	if (!str)
		return (0);
	new_str = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (new_str[i] == (unsigned char) c)
			return ((void *)str + i);
		i++;
	}
	return (0);
}

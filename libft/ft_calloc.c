/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:49:58 by gnyssens          #+#    #+#             */
/*   Updated: 2024/04/18 14:29:57 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void			*ptr;
	size_t			aantal;

	aantal = n * size;
	if (size != 0 && (aantal / size) != n)
		return (NULL);
	ptr = (void *)malloc(aantal);
	if (!ptr)
		return (0);
	ft_bzero(ptr, n * size);
	return (ptr);
}

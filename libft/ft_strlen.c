/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:10:59 by gnyssens          #+#    #+#             */
/*   Updated: 2024/09/26 18:26:52 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *src)
{
	size_t				i;
	unsigned const char	*new_src;

	if (!src)
		return (0);
	new_src = (unsigned const char *)src;
	i = 0;
	while (new_src[i])
		i++;
	return (i);
}


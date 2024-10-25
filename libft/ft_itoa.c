/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:53:57 by gnyssens          #+#    #+#             */
/*   Updated: 2024/08/20 15:57:46 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(int n)
{
	int	res;

	if (n == -2147483648)
		return (11);
	res = 1;
	if (n < 0)
	{
		n *= (-1);
		res++;
	}
	while (n > 9)
	{
		res++;
		n = n / 10;
	}
	return (res);
}

static int	ten_exp(int n)
{
	int	res;

	if (n == 0)
		return (1);
	res = 10;
	while (n > 1)
	{
		res *= 10;
		n--;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		i;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = length(n);
	result = (char *)malloc(len + 1);
	if (!result)
		return (0);
	i = 0;
	if (n < 0)
	{
		result[i++] = '-';
		n *= (-1);
		len--;
	}
	while (len > 0)
	{
		result[i++] = (n / ten_exp(len - 1)) + '0';
		n = (n % ten_exp(len - 1));
		len--;
	}
	result[i] = '\0';
	return (result);
}

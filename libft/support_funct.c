/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_funct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:22:38 by gnyssens          #+#    #+#             */
/*   Updated: 2024/04/24 17:44:32 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	my_put_nbr(int n, int *count_ptr)
{
	char	c;

	if (n < 0)
	{
		write(1, "-", 1);
		(*count_ptr)++;
		n *= (-1);
	}
	if (n >= 10)
	{
		my_put_nbr(n / 10, count_ptr);
		n = n % 10;
	}
	if (n <= 9)
	{
		c = n + '0';
		write(1, &c, 1);
		(*count_ptr)++;
	}
}

void	my_put_u(unsigned int n, int *count_ptr)
{
	char	c;

	if (n >= 10)
	{
		my_put_u(n / 10, count_ptr);
		n = n % 10;
	}
	if (n <= 9)
	{
		c = n + '0';
		write(1, &c, 1);
		(*count_ptr)++;
	}
}

void	put_address(unsigned long long nbr, int *count_ptr)
{
	char	*base;

	base = "0123456789abcdef";
	if (nbr > 15)
	{
		put_address(nbr / 16, count_ptr);
		nbr = nbr % 16;
	}
	if (nbr <= 15)
	{
		write(1, &base[nbr], 1);
		(*count_ptr)++;
	}
}

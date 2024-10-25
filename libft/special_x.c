/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:05:25 by gnyssens          #+#    #+#             */
/*   Updated: 2024/04/25 15:23:31 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_hexa(unsigned int nb, int *count_ptr)
{
	char	*base;

	base = "0123456789abcdef";
	if (nb > 15)
	{
		put_hexa(nb / 16, count_ptr);
		nb = nb % 16;
	}
	if (nb <= 15)
	{
		write(1, &base[nb], 1);
		(*count_ptr)++;
	}
}

void	write_hexa(const char **dptr_f, int *count_ptr, va_list *arg_ptr)
{
	unsigned int	nbr;

	nbr = (unsigned int) va_arg(*arg_ptr, unsigned int);
	put_hexa(nbr, count_ptr);
	(*dptr_f)++;
}

void	put_maj_hexa(unsigned int nb, int *count_ptr)
{
	char	*base;

	base = "0123456789ABCDEF";
	if (nb > 15)
	{
		put_maj_hexa(nb / 16, count_ptr);
		nb = nb % 16;
	}
	if (nb <= 15)
	{
		write(1, &base[nb], 1);
		(*count_ptr)++;
	}
}

void	write_maj_hexa(const char **dptr_f, int *count_ptr, va_list *arg_ptr)
{
	unsigned int	nbr;

	nbr = (unsigned int) va_arg(*arg_ptr, unsigned int);
	put_maj_hexa(nbr, count_ptr);
	(*dptr_f)++;
}

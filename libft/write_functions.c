/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:03:16 by gnyssens          #+#    #+#             */
/*   Updated: 2024/04/25 15:23:43 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_char(const char **dptr_f, int *ptr_count, va_list *arg_ptr)
{
	char	c;

	c = (char)va_arg(*arg_ptr, int);
	write(1, &c, 1);
	(*dptr_f)++;
	(*ptr_count)++;
}

void	write_string(const char **dptr_f, int *ptr_count, va_list *arg_ptr)
{
	char	*str;

	str = va_arg(*arg_ptr, char *);
	if (!str)
		str = "(null)";
	while (*str != '\0')
	{
		write(1, str, 1);
		(*ptr_count)++;
		str++;
	}
	(*dptr_f)++;
}

void	write_int(const char **dptr_f, int *count_ptr, va_list *arg_ptr)
{
	int	nb;

	nb = va_arg(*arg_ptr, int);
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		*count_ptr += 11;
	}
	else
		my_put_nbr(nb, count_ptr);
	(*dptr_f)++;
}

void	write_u(const char **dptr_f, int *count_ptr, va_list *arg_ptr)
{
	unsigned int	nb;

	nb = va_arg(*arg_ptr, unsigned int);
	my_put_u(nb, count_ptr);
	(*dptr_f)++;
}

void	write_address(const char **dptr_f, int *count_ptr, va_list *arg_ptr)
{
	unsigned long long	value;

	value = (unsigned long long) va_arg(*arg_ptr, void *);
	if (0 == value)
	{
		write(1, "0x0", 3);
		(*count_ptr) += 3;
		(*dptr_f)++;
		return ;
	}
	else
	{
		write(1, "0x", 2);
		(*count_ptr) += 2;
		put_address(value, count_ptr);
	}
	(*dptr_f)++;
}

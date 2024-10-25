/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:58:38 by gnyssens          #+#    #+#             */
/*   Updated: 2024/04/25 15:15:28 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	simply_write(const char **dptr_f, int *count_ptr)
{
	write(1, *dptr_f, 1);
	(*count_ptr)++;
	(*dptr_f)++;
}

void	specifier(const char **dptr_f, int *count_ptr, va_list *arg_ptr)
{
	(*dptr_f)++;
	if (*(*dptr_f) == '%')
		simply_write(dptr_f, count_ptr);
	else if (*(*dptr_f) == 'c')
		write_char(dptr_f, count_ptr, arg_ptr);
	else if (*(*dptr_f) == 's')
		write_string(dptr_f, count_ptr, arg_ptr);
	else if (*(*dptr_f) == 'd' || *(*dptr_f) == 'i')
		write_int(dptr_f, count_ptr, arg_ptr);
	else if (*(*dptr_f) == 'u')
		write_u(dptr_f, count_ptr, arg_ptr);
	else if (*(*dptr_f) == 'p')
		write_address(dptr_f, count_ptr, arg_ptr);
	else if (*(*dptr_f) == 'x')
		write_hexa(dptr_f, count_ptr, arg_ptr);
	else if (*(*dptr_f) == 'X')
		write_maj_hexa(dptr_f, count_ptr, arg_ptr);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	va_start(args, format);
	count = 0;
	while (*format != '\0')
	{
		if (*format != '%')
			simply_write(&format, &count);
		else
			specifier(&format, &count, &args);
	}
	va_end(args);
	return (count);
}

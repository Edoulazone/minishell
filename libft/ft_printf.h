/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:59:45 by gnyssens          #+#    #+#             */
/*   Updated: 2024/04/24 17:33:14 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

// LIBRARIES

# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>

// PROTOTYPES FONCTIONS

void	simply_write(const char **dptr_f, int *count_ptr);
void	write_char(const char **dptr_f, int *ptr_count, va_list *arg_ptr);
void	write_string(const char **dptr_f, int *ptr_count, va_list *arg_ptr);
void	write_int(const char **dptr_f, int *count_ptr, va_list *arg_ptr);
void	my_put_nbr(int n, int *count_ptr);
void	my_put_u(unsigned int n, int *count_ptr);
void	write_u(const char **dptr_f, int *count_ptr, va_list *arg_ptr);
void	write_address(const char **dptr_f, int *count_ptr, va_list *arg_ptr);
void	put_address(unsigned long long nbr, int *count_ptr);
void	specifier(const char **dptr_format, int *count_ptr, va_list *arg_ptr);
int		ft_printf(const char *format, ...);

// PROTOTYPES POUR HEXA

void	write_hexa(const char **dptr_f, int *count_ptr, va_list *arg_ptr);
void	put_hexa(unsigned int nb, int *count_ptr);
void	write_maj_hexa(const char **dptr_f, int *count_ptr, va_list *arg_ptr);
void	put_maj_hexa(unsigned int nb, int *count_ptr);

#endif
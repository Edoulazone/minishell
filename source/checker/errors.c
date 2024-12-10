/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:48:01 by eschmitz          #+#    #+#             */
/*   Updated: 2024/11/28 14:53:15 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Écrit le message d'erreur et retourne une erreur
int	ft_error(char *str, int n, char var)
{
	int	i;

	i = -1;
	if (!str)
		return (1);
	while (str[++i])
	{
		if (str[i] == '\'' && str[i - 1] == '\'')
			while (n-- > 0)
				write(1, &var, 1);
		write(1, &str[i], 1);
	}
	return (EXIT_FAILURE);
}

void	error(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	//exit(1);
}

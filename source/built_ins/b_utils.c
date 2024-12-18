/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:25:17 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/12 16:19:25 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*safe_malloc(unsigned int size)
{
	void	*result;

	result = malloc(size);
	if (!result)
	{
		write(1, "Malloc failed !, Exiting program\n", 33);
		exit(EXIT_FAILURE);
	}
	return (result);
}

char	*safe_strdup(char *str)
{
	char	*result;

	result = ft_strdup(str);
	if (!result)
	{
		write(2, "ft_strdup failed !\n", 19);
		exit(EXIT_FAILURE);
	}
	return (result);
}

void	free_split(char **mem)
{
	int	i;

	i = 0;
	while (mem[i] != NULL)
	{
		free(mem[i]);
		i++;
	}
	free(mem);
}

char	*safe_strjoin(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (!result)
	{
		write(2, "strjoin fail !, Exiting\n", 24);
		exit(EXIT_FAILURE);
	}
	return (result);
}

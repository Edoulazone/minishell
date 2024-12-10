/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:25:17 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/10 15:59:37 by eschmitz         ###   ########.fr       */
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
	char *result;

	result = ft_strdup(str);
	if (!result)
	{
		//sans doute faudrait free "t_shell -> tout" ici pr etre parfait
		write(1, "ft_strdup failed !\n", 19);
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
		write(1, "strjoin faile !, Exiting\n", 25);
		exit(EXIT_FAILURE); //faudra surement strerror etc.
	}
	return (result);
}

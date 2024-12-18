/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:51:05 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/18 14:52:46 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_there_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	filler(char **array, t_env *env, int *i)
{
	char	*temp;
	char	*save;

	temp = safe_strjoin(env->value, "=");
	save = temp;
	temp = safe_strjoin(temp, env->content);
	free(save);
	array[*i] = safe_strdup(temp);
	free(temp);
}

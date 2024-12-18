/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:24:51 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/13 14:14:09 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_paths(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->value, "PATH") == 0 && env->content)
			return (env->content);
		else
			env = env->next;
	}
	return (NULL);
}

char	*find_home(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->value, "HOME") == 0 && env->content)
			return (env->content);
		else
			env = env->next;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:24:51 by gnyssens          #+#    #+#             */
/*   Updated: 2024/10/21 16:57:30 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//sans MALLOC
char	*find_paths(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->value, "PATH") == 0 && env->content)
			return (env->content);
		else
			env = env->next;
	}
	write(1, "variable PATH pas trouvee !\n", 28); //à supprimer
	return (NULL);
}

//sans MALLOC
char	*find_home(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->value, "HOME") == 0 && env->content)
			return (env->content);
		else
			env = env->next;
	}
	write(1, "variable HOME pas trouvee !\n", 28); //à supprimer
	return (NULL);
}

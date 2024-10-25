/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:24:51 by gnyssens          #+#    #+#             */
/*   Updated: 2024/10/09 16:22:53 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//sans MALLOC
char	*find_paths(t_list *env)
{
	while (env)
	{
		if (ft_strncmp(env->content, "PATH=", 5) == 0)
			return ((env->content) + 5);
		else
			env = env->next;
	}
	write(1, "variable PATH pas trouvee !\n", 28); //à supprimer
	return (NULL);
}

//sans MALLOC
char	*find_home(t_list *env)
{
	while (env)
	{
		if (ft_strncmp(env->content, "HOME=", 5) == 0)
			return ((env->content) + 5);
		else
			env = env->next;
	}
	write(1, "variable HOME pas trouvee !\n", 28); //à supprimer
	return (NULL);
}

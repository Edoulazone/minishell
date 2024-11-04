/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:28:41 by gnyssens          #+#    #+#             */
/*   Updated: 2024/10/21 17:35:27 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//changer tous les t_list en t_env
void	ft_cd(t_ast *cmd, t_env *env)
{
	//int		i;
	char	*path;

	if (cmd->value[2]) // == ya trop d'arguments pr juste le PATH
	{
		write(1, "too many arguments !\n", 21);
		return ;
	}
	if (!(cmd->value[1]))
	{
		path = find_home(env);
		if (!path)
			write(1, "probleme avec HOME ! \n", 22);
		if (chdir(path) != 0)
			write(1, "chdir didn't work !\n", 20); //faudra surement faire autre chose
		return ;
	}
	else
		path = cmd->value[1];
	if (chdir(path) != 0)
		write(1, "chdir didn't work, wrong PATH !\n", 32);
}

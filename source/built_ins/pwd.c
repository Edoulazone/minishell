/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:58:47 by gnyssens          #+#    #+#             */
/*   Updated: 2024/10/08 17:01:19 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//p-e qu'il faudra qd mm utiliser t_shell, et sans doute qu'il faudra sauver qql infos, et gerer 'errno'
void	ft_pwd(t_shell *sh)
{
	char	*path;

	(void)sh; //ne sert a rien a priori, p-e apres
	path = getcwd(NULL, 0);
	if (!path)
		perror("getcwd failed !\n");
	else
	{
		write(1, path, ft_strlen(path));
		write(1, "\n", 1);
	}
}

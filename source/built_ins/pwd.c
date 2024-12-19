/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:58:47 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/19 13:10:40 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_old_pwd(t_env *env)
{
	while (env->next && ft_strcmp(env->value, "OLDPWD") != 0)
		env = env->next;
	if (env && !ft_strcmp(env->value, "OLDPWD"))
		return (env->content);
	my_write(2, "minishell: cd: OLDPWD not set\n", 2);
	return (NULL);
}

void	ft_pwd(t_shell *sh)
{
	char	*path;

	(void)sh;
	g_exit_status = 0;
	path = getcwd(NULL, 0);
	if (!path)
	{
		my_write(2, "getcwd: cannot access parent directories", 1);
		my_write(2, ": No such file or directory\n", 1);
	}
	else
	{
		write(1, path, ft_strlen(path));
		write(1, "\n", 1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:33:50 by eschmitz          #+#    #+#             */
/*   Updated: 2024/10/24 15:30:44 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Initialiser le shell
void	shell_init(t_shell *sh)
{
	sh->str = NULL;
	sh->token = NULL;
	sh->command = NULL;
	sh->ast = NULL;
	sh->delimiter = NULL;
	sh->exit_status = ft_strdup("0");
	if (!sh->exit_status)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:33:50 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/10 18:26:42 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Initialiser le shell
int	shell_init(t_shell *sh)
{
	sh->str = NULL;
	sh->token = NULL;
	sh->command = NULL;
	sh->ast = NULL;
	sh->delimiter = NULL;
	sh->token = NULL;
	sh->expander = NULL;
	sh->exit_status = 0;//ft_strdup("0");
	if (sh->exit_status)
		return (1);
	return (0);
}

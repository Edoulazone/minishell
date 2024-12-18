/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:33:50 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/18 17:37:37 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_init(t_shell *sh)
{
	sh->str = NULL;
	sh->token = NULL;
	sh->command = NULL;
	sh->ast = NULL;
	sh->delimiter = NULL;
	sh->expander = NULL;
	sh->loop = 0;
	if (!g_exit_status)
		g_exit_status = 0;
	return (0);
}

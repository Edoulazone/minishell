/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_trunc_append.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:07:49 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/18 13:41:36 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_trunc_append(t_redir *node, t_env **env, t_shell *sh)
{
	int	fd;

	if (node->type == TRUNC)
		fd = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		exit(1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	execute_ast(node->cmd, env, sh);
}

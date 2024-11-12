/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_trunc_append.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:07:49 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/06 15:30:49 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    handle_trunc_append(t_ast *node, t_env **env, t_shell *sh)
{
    int     fd;
    pid_t   pid;
    
	if (node->n_type == TRUNC)
		fd = open(node->value[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(node->value[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return ;
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE); // == problem with fork() !
	if (0 == pid)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
		execute_ast(node->left, env, sh);
	}
	else
	{
		close(fd);
		waitpid(pid, &sh->exit_status, 0);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:05:37 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/06 15:30:37 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    handle_input(t_ast *node, t_env **env, t_shell *sh)
{
    int     fd;
    pid_t   pid;
    
	fd = open(node->value[0], O_RDONLY);
	if (fd < 0)
		return ;
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE); // == problem with fork() !
	if (0 == pid)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		execute_ast(node->left, env, sh); // p-e que ce sera right-child
	}
	else
	{
		close(fd); //close file descriptor dans le parent process
		waitpid(pid, &sh->exit_status, 0);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:41:10 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/05 17:04:33 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	decoupage_left_pipe(int *pipe_fd, t_ast *node, t_env **env, t_shell *sh)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	execute_ast(node->left, env, sh);
}

void	decoupage_right_pipe(int *pipe_fd, t_ast *node, t_env **env, t_shell *sh)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	execute_ast(node->right, env, sh);
}

void    handle_pipe(t_ast *node, t_env **env, t_shell *sh)
{
	pid_t	pid;
	int		pipe_fd[2];
	
    if (-1 == pipe(pipe_fd))
		exit(EXIT_FAILURE); //p-e juste return (EXIT_FAILURE), et perror
    pid = fork();
    if (pid < 0)
		exit(EXIT_FAILURE); // == problem with fork() !
	if (0 == pid) //handle left child
		decoupage_left_pipe(pipe_fd, node, env, sh);
	else
		waitpid(pid, &sh->return_value, 0);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE); // == problem with fork() !
	if (0 == pid) //handle right child
		decoupage_left_pipe(pipe_fd, node, env, sh);
	else
		waitpid(pid, &sh->return_value, 0);
	close(pipe_fd[0]); // je sais pas si ils doivent
	close(pipe_fd[1]); // etre ici ou dans ELSE
}

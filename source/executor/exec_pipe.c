/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:41:10 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/18 18:21:44 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exit_status(int status)
{
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
}

void	handle_dup2(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		exit(EXIT_FAILURE);
}

void	right_pid(t_pipe *node, t_env **env, t_shell *sh, int *pipe_fd)
{
	close(pipe_fd[1]);
	handle_dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	execute_ast(node->right, env, sh);
	exit(EXIT_FAILURE);
}

void	left_pid(t_pipe *node, t_env **env, t_shell *sh, int *pipe_fd)
{
	close(pipe_fd[0]);
	handle_dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	execute_ast(node->left, env, sh);
	exit(EXIT_FAILURE);
}

void	handle_pipe(t_pipe *node, t_env **env, t_shell *sh)
{
	int		pipe_fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;

	if (pipe(pipe_fd) == -1)
		exit(EXIT_FAILURE);
	pid_left = fork();
	if (pid_left < 0)
		exit(EXIT_FAILURE);
	if (pid_left == 0)
		left_pid(node, env, sh, pipe_fd);
	pid_right = fork();
	if (pid_right < 0)
		exit(EXIT_FAILURE);
	if (pid_right == 0)
		right_pid(node, env, sh, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid_left, &status, 0);
	set_exit_status(status);
	waitpid(pid_right, &status, 0);
	set_exit_status(status);
}

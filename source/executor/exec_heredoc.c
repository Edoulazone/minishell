/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:54:02 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/04 18:37:50 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_heredoc(t_ast *node, t_env **env, t_shell *sh)
{
	pid_t	pid;
	char	*line;
	int		pipe_fd[2];

	if (-1 == pipe(pipe_fd))
    {
		perror("pipe failed !"); //jsp si ca suffit
    	exit(EXIT_FAILURE); //p-e juste return (EXIT_FAILURE)
    }
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(node->value[0], line) == 0) //ca c'est si line == End Of File, spécifié dans value[0]
		{
			free(line);
			break;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (0 == pid)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		execute_ast(node->left, env, sh);
	}
	else
	{
		close(pipe_fd[0]);
		waitpid(pid, &sh->exit_status, 0);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:54:02 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/26 14:52:31 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	quand un node est '<<' ou nptq quelle autre redirection 
	il faudra mettre EOF (ou le infile/outfile) dans le node->value (char **)
	de la redirection, PAS dans son right child comme mnt, sinon le code ne marchera
	pas pour des commandes tel que: `cat <<eof | cat`
*/

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
		line = readline("heredoc> ");
		if (!line || ft_strcmp(node->right->value[0], line) == 0)
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

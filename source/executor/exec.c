/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:22:50 by gnyssens          #+#    #+#             */
/*   Updated: 2024/10/31 17:29:08 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	IL Y AURA SANS DOUTE UN `RETURN VALUE` EN VARIABLE GLOBALE !
*/

int is_built_in(t_ast *cmd, t_env **env, t_shell *sh)
{
    char **args;

    args = cmd->value;
    if (ft_strcmp(args[0], "echo") == 0)
        return (ft_echo(cmd), 1);
    if (ft_strcmp(args[0], "cd") == 0)
        return (ft_cd(cmd, *env), 1);
    if (ft_strcmp(args[0], "pwd") == 0)
        return (ft_pwd(sh), 1);
    if (ft_strcmp(args[0], "export") == 0)
        return (ft_export(cmd, env), 1);
    if (ft_strcmp(args[0], "unset") == 0)
        return (ft_unset(cmd, env), 1);
    if (ft_strcmp(args[0], "env") == 0)
        return (ft_env(*env), 1);
    if (ft_strcmp(args[0], "exit") == 0)
        return(exit(EXIT_SUCCESS), 1); //bon ici ca ne free pas proprement
    return (0);
}

// faudra raccourcir la fonction en la découpant
// je laisse comme ca pr la lisibilité
int execute_ast(t_ast *node, t_env **env, t_shell *sh)
{
	int		fd;
    int     pipe_fd[2];
    pid_t   pid;

    if (!node)
        return (EXIT_SUCCESS);
    if (node->n_type == CMD)
    {
        if (!(is_built_in(node, env, sh)))
        {
            pid = fork();
            if (pid < 0)
                exit(EXIT_FAILURE); // == problem with fork() !
            else if (0 == pid)
                execute_command(node, *env, sh);
            else
                waitpid(pid, &sh->return_value, 0); //wait for
        }
    }
    else if (node->n_type == PIPE)
    {
        if (-1 == pipe(pipe_fd))
        {
            perror("pipe failed !"); //jsp si ca suffit
            exit(EXIT_FAILURE); //p-e juste return (EXIT_FAILURE)
        }
        pid = fork();
        if (pid < 0)
			exit(EXIT_FAILURE); // == problem with fork() !
		if (0 == pid) //handle left child
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			execute_ast(node->left, env, sh);
		}
		else
			waitpid(pid, &sh->return_value, 0);
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE); // == problem with fork() !
		if (0 == pid) //handle right child
		{
			close(pipe_fd[1]);
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
			execute_ast(node->right, env, sh);
		}
		else
			waitpid(pid, &sh->return_value, 0);
		close(pipe_fd[0]); // je sais pas si ils doivent
		close(pipe_fd[1]); // etre ici ou dans ELSE
    }
	else if (node->n_type == INPUT)
	{
		fd = open(node->value[0], O_RDONLY);
		if (fd < 0)
			return (perror("open failed !"), EXIT_FAILURE);
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
	
}

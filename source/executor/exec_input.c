/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:05:37 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/06 23:20:57 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_split(char **ptr)
{
	int	i;

	i = 0;
	printf("[");
	while (ptr[i])
	{
		printf("\"%s\", ", ptr[i]);
		i++;
	}
	printf("]\n");
}

//p-e qu'il faudra pas fork enft
void    handle_input(t_redir *node, t_env **env, t_shell *sh)
{
    int     fd;
    //pid_t   pid;
    
	fd = open(node->file, O_RDONLY);
	if (fd < 0)
		return ;
	//pid = fork();
	//if (pid < 0)
	//	exit(EXIT_FAILURE); // == problem with fork() !
	//if (0 == pid)
	//print_split(((t_cmd *)(node->cmd))->arg);
	dup2(fd, STDIN_FILENO);
	close(fd);

	execute_ast(node->cmd, env, sh); // p-e que ce sera right-child
	
	/*
	else
	{
		close(fd); //close file descriptor dans le parent process
		waitpid(pid, &sh->exit_status, 0);
	}
	*/
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:57:17 by eschmitz          #+#    #+#             */
/*   Updated: 2024/10/15 18:37:28 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	ft_cd(char **argv)
{
	if (argv[1] == NULL)
		write(2, "Expected argument for cd\n", 25);
	else if (chdir(argv[1]) != 0)
		perror("cd");
}

void	ft_exit(void)
{
	exit(0);
}

void	ft_echo(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		write(1, argv[i], strlen(argv[i]));
		write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

void	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd");
}

void	execute_command(char **argv)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(argv[0], argv) == -1)
			perror("execvp");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		perror("fork");
	else
		waitpid(pid, NULL, 0);
}
*/
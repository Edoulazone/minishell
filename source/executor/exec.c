/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:22:50 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/18 17:40:33 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status(void)
{
	int	status;

	wait(&status);
	if (WIFEXITED(status))
	{
		g_exit_status = WEXITSTATUS(status);
	}
}

void	pre_ast(t_ast *node, t_env **env, t_shell *sh)
{
	pid_t	pid;
	int		status;

	if (node->type == CMD)
	{
		if (is_built_in((t_cmd *)node, env, sh))
			return ;
	}
	handle_signal(1);
	pid = fork();
	if (pid < 0)
		exit(g_exit_status);
	if (pid == 0)
		execute_ast(node, env, sh);
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (g_exit_status <= 126)
			g_exit_status = WEXITSTATUS(status);
		set_exit_status(status);
	}
}

int	is_built_in(t_cmd *node, t_env **env, t_shell *sh)
{
	char	**args;

	args = node->arg;
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(node), 1);
	if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(node, *env, NULL), 1);
	if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd(sh), 1);
	if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(node, env), 1);
	if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(node, env), 1);
	if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(*env), 1);
	if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(node, sh), 1);
	return (0);
}

void	execute_ast(t_ast *node, t_env **env, t_shell *sh)
{
	g_exit_status = 0;
	if (!node)
		return ;
	if (node->type == CMD)
	{
		if (!is_built_in((t_cmd *)node, env, sh))
			execute_command((t_cmd *)node, *env);
		else
			return ;
	}
	else if (node->type == PIPE)
		handle_pipe((t_pipe *)node, env, sh);
	else if (node->type == INPUT || node->type == HEREDOC)
		handle_input((t_redir *)node, env, sh);
	else if (node->type == TRUNC || node->type == APPEND)
		handle_trunc_append((t_redir *)node, env, sh);
	exit(g_exit_status);
}

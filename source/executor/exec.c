/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:22:50 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/06 23:20:37 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pre_ast(t_ast *node, t_env **env, t_shell *sh)
{
	pid_t	pid;

	if (node->type == CMD)
	{
		if (is_built_in((t_cmd *)node, env, sh))
			return ;
	}
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE); //bref
	if (pid == 0)
	{
		execute_ast(node, env, sh);
	}
	else
		waitpid(pid, &sh->exit_status, 0);
}

// sert à checker si la commande est built-in (ne necessite pas de fork etc.)
int is_built_in(t_cmd *node, t_env **env, t_shell *sh)
{
	char	**args;

	args = node->arg;
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(node), 1);
	if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(node, *env), 1);
	if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd(sh), 1);
	if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(node, env), 1);
	if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(node, env), 1);
	if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(*env), 1);
	if (ft_strcmp(args[0], "exit") == 0)
		return(exit(EXIT_SUCCESS), 1); //bon ici ca ne free pas proprement
	return (0);
}

// fonction principale de l'EXEC
// recursion de la root jusqu'à ce que tout ai été exécuté
// check le type de chaque node et délègue aux fonctions compétentes en réaction
int execute_ast(t_ast *node, t_env **env, t_shell *sh)
{
	//pid_t	pid;

	if (!node)
		return (write(1, "node est NULL\n", 14), EXIT_SUCCESS);
    if (node->type == CMD)
    {
		if (!is_built_in((t_cmd *)node, env, sh))
			execute_command((t_cmd *)node, *env, sh);
		else 
			return (0); //ligne inutile je crois
    }
    else if (node->type == PIPE)
        handle_pipe((t_pipe *)node, env, sh);
	else if (node->type == INPUT || node->type == HEREDOC)
		handle_input((t_redir *)node, env, sh);
	else if (node->type == TRUNC || node->type == APPEND)
		handle_trunc_append((t_redir *)node, env, sh);
	return (0);
}

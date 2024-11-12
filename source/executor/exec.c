/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:22:50 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/05 17:09:45 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	IL Y AURA SANS DOUTE UN `RETURN VALUE` EN VARIABLE GLOBALE !
*/

// sert à checker si la commande est built-in (ne necessite pas de fork etc.)
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

// fonction principale de l'EXEC
// recursion de la root jusqu'à ce que tout ai été exécuté
// check le type de chaque node et délègue aux fonctions compétentes en réaction
int execute_ast(t_ast *node, t_env **env, t_shell *sh)
{
    if (!node)
        return (EXIT_SUCCESS);
    if (node->n_type == CMD)
    {
        if (!(is_built_in(node, env, sh)))
			handle_cmd(node, env, sh);
    }
    else if (node->n_type == PIPE)
    {
        handle_pipe(node, env, sh);
    }
	else if (node->n_type == INPUT)
		handle_input(node, env, sh);
	else if (node->n_type == TRUNC || node->n_type == APPEND)
		handle_trunc_append(node, env, sh);
	else if (node->n_type == HEREDOC)
		handle_heredoc(node, env, sh);
	return (0);
}

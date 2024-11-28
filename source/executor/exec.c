/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:22:50 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/21 17:57:23 by gnyssens         ###   ########.fr       */
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

void	print_value(char **arg)
{
	int	i;
	int	j;

	if (arg == NULL)
	{
		write(1, "node->value is NULL !\n", 22);
		return ;
	}
	j = 0;
	write(2, "node->value: ", 13);
	while (arg[j] != NULL)
	{
		i = 0;
		write(2, "\"", 1);
		while (arg[j][i])
		{
			write(2, arg[j] + i, 1);
			i++;
		}
		write(2, "\"", 1);
		if (arg[j + 1])
			write(2, ", ", 2);
		j++;
	}
	write(1, "\n", 1);
}

// fonction principale de l'EXEC
// recursion de la root jusqu'à ce que tout ai été exécuté
// check le type de chaque node et délègue aux fonctions compétentes en réaction
int execute_ast(t_ast *node, t_env **env, t_shell *sh)
{
	if (!node)
	{
		return (write(1, "node est NULL\n", 14), EXIT_SUCCESS);
	}
	//print_value(node->value);
    if (node->n_type == CMD)
    {
		write(1, "node->n_type is a COMMAND\n", 26);
		print_value(node->value);
        if (!(is_built_in(node, env, sh)))
			handle_cmd(node, env, sh);
		else 
			return (0); //pas sur ici
    }
    else if (node->n_type == PIPE)
    {
		write(1, "node->n_type is a PIPE\n", 23);
		print_value(node->value);
        handle_pipe(node, env, sh);
    }
	else if (node->n_type == INPUT)
    {
		write(1, "node->n_type is INPUT\n", 22);
		print_value(node->value);
		handle_input(node, env, sh);
    }
	else if (node->n_type == TRUNC || node->n_type == APPEND)
	{
		write(1, "node->n_type is a > or >>\n", 26);
		print_value(node->value);
		handle_trunc_append(node, env, sh);
	}
	else if (node->n_type == HEREDOC)
	{
		write(1, "node->n_type is a HEREDOC\n", 26);
		print_value(node->value);
		print_value(node->left->value);
		print_value(node->right->value);
		write(1, "type du right child: ", 22);
		char test = node->right->n_type + '0';
		write(1, &test, 1);
		write(1, "\n", 1);
		handle_heredoc(node, env, sh);
	}
	return (0);
}

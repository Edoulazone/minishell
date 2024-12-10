/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hardcode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:48:49 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/04 17:02:11 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//test COMMANDE: `cat Makefile`
t_ast *hard_ast1(t_shell *sh)
{
    t_cmd   *node;
    char    command[] = "cat Makefile";

    node = (t_cmd *)malloc(sizeof(t_cmd));
    node->type = CMD;
    node->arg = ft_split(command, ' ');
    node->env = sh->env;

    return ((t_ast *)node);
}

//test PIPE: `cat Makefile | grep source`
t_ast *hard_ast2(t_shell *sh)
{
    t_pipe   *node;
    char    cmd1[] = "cat Makefile";
    char    cmd2[] = "grep source";
    t_cmd   *left;
    t_cmd   *right;

    node = (t_pipe *)malloc(sizeof(t_pipe));
    node->type = PIPE;

    left = (t_cmd *)malloc(sizeof(t_cmd));
    left->type = CMD;
    left->env = sh->env;
    left->arg = ft_split(cmd1, ' ');

    right = (t_cmd *)malloc(sizeof(t_cmd));
    right->type = CMD;
    right->env = sh->env;
    right->arg = ft_split(cmd2, ' ');

	node->left = (t_ast *)left;
	node->right = (t_ast *)right;

    return ((t_ast *)node);
}

// test HEREDOC: `cat <<eof`
t_ast *hard_ast3(t_shell *sh)
{
	t_redir	*node;
	t_cmd	*command;

	command = (t_cmd *)malloc(sizeof(t_cmd));
	command->type = CMD;
	command->env = sh->env;
	command->arg = ft_split("cat ", ' ');

	node = (t_redir *)malloc(sizeof(t_redir));
	node->type = HEREDOC;
	node->file = safe_strdup("eof");
	node->cmd = (t_ast *)command;

	return ((t_ast *)node);
}

//test INPUT: cat < infile
t_ast *hard_ast4(t_shell *sh)
{
	t_redir	*node;
	t_cmd	*command;

	command = (t_cmd *)malloc(sizeof(t_cmd));
	command->type = CMD;
	command->env = sh->env;
	command->arg = ft_split("cat", ' ');

	node = (t_redir *)malloc(sizeof(t_redir));
	node->type = INPUT;
	node->file = safe_strdup("infile");
	node->cmd = (t_ast *)command;

	return ((t_ast *)node);
}

//test TRUNC (>): cat infile > outfile
t_ast *hard_ast5(t_shell *sh)
{
	t_redir	*node;
	t_cmd	*command;

	command = (t_cmd *)malloc(sizeof(t_cmd));
	command->type = CMD;
	command->env = sh->env;
	command->arg = ft_split("cat Makefile", ' ');

	node = (t_redir *)malloc(sizeof(t_redir));
	node->type = TRUNC;
	node->file = safe_strdup("outfile");
	node->cmd = (t_ast *)command;

	return ((t_ast *)node);
}

// test built-ins: export
t_ast *hard_ast6(t_shell *sh)
{
    t_cmd   *node;
    char    command[] = "export";

    node = (t_cmd *)malloc(sizeof(t_cmd));
    node->type = CMD;
    node->arg = ft_split(command, ' ');
    node->env = sh->env;

    return ((t_ast *)node);
}

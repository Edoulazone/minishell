/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:14:51 by eschmitz          #+#    #+#             */
/*   Updated: 2024/11/27 17:23:27 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Vérifie si c'est une commande ou un argument
int	is_command(int type)
{
	if (type == CMD || type == ARG)
		return (0);
	return (1);
}

//Vérifie si les redirections sont possiblement faisables
int	verif_redirect(t_token *current_t)
{
	if (current_t->next == NULL || is_command(current_t->next->t_type) == 1)
		return (ft_error("ERROR PIPE\n", 0, 0));
	return (0);
}

//Vérifie le type et l'existence des tokens
int	verif_token(t_shell *sh)
{
	int		verif;
	t_token	*temp;

	verif = 0;
	temp = sh->token;
	if (temp->t_type == PIPE && temp->next == NULL)
		return (ft_error(SYNTAX_ERROR, '|', 1));
	while (temp != NULL)
	{
		if (temp->t_type == TRUNC || temp->t_type == INPUT
			|| temp->t_type == APPEND || temp->t_type == HEREDOC)
			verif = verif_redirect(temp);
		temp = temp->next;
		if (verif != 0)
        {
            sh->exit_status = 258;
			return (verif);
        }
	}
	return (verif);
}


// // Helper function to print indentation based on tree level
// void print_indent(int level)
// {
//     for (int i = 0; i < level; i++)
//         printf("    ");
// }

// // Function to print command nodes
// void print_cmd(t_ast *node, int level)
// {
//     print_indent(level);
//     printf("CMD: ");
//     for (int i = 0; node->value && node->value[i]; i++)
//         printf("%s ", node->value[i]);
//     printf("\n");
// }

// // Function to print redirection nodes
// void print_redir(t_ast *node, int level)
// {
//     print_indent(level);
//     if (node->n_type == INPUT)
//         printf("INPUT REDIR: %s\n", node->value ? node->value[0] : "(null)");
//     else if (node->n_type == APPEND)
//         printf("APPEND OUTPUT: %s\n", node->value ? node->value[0] : "(null)");
//     else if (node->n_type == TRUNC)
//         printf("OUTPUT REDIR: %s\n", node->value ? node->value[0] : "(null)");
//     else if (node->n_type == HEREDOC)
//         printf("HEREDOC: %s\n", node->value ? node->value[0] : "(null)");
// }

// // Function to print pipe nodes
// void print_pipe(t_ast *node, int level)
// {
//     print_indent(level);
//     printf("PIPE:\n");

//     print_indent(level + 1);
//     printf("LEFT:\n");
//     if (node->left)
//         ast_printer(node->left, level + 2);
//     else
//     {
//         print_indent(level + 2);
//         printf("(null)\n");
//     }

//     print_indent(level + 1);
//     printf("RIGHT:\n");
//     if (node->right)
//         ast_printer(node->right, level + 2);
//     else
//     {
//         print_indent(level + 2);
//         printf("(null)\n");
//     }
// }

// // Main recursive AST printer
// void ast_printer(t_ast *node, int level)
// {
//     if (!node)
//         return;

//     switch (node->n_type)
//     {
//     case CMD:
//         print_cmd(node, level);
//         break;
//     case PIPE:
//         print_pipe(node, level);
//         break;
//     case INPUT:
//     case APPEND:
//     case TRUNC:
//     case HEREDOC:
//         print_redir(node, level);
//         break;
//     default:
//         print_indent(level);
//         printf("Unknown node type\n");
//     }
// }

//Gère le déroulement général du parsing
int	parsing(t_shell *sh)
{
	if (verif_token(sh) > 0)
	{
		return (EXIT_FAILURE);
	}
    if (verif_tokens(sh, sh->token) > 0)
	{
    	return (EXIT_FAILURE);
	}
	sh->ast = make_ast(sh->token);
	if (!sh->ast)
	{
		return (EXIT_FAILURE);
	}
	// ast_printer(sh->ast, 0);
	return (EXIT_SUCCESS);
}
 
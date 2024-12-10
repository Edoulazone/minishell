/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:24:35 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/10 16:10:48 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstfind(t_token *token, int type)
{
	if (!token)
		return (EXIT_FAILURE);
	if (type == REDIR)
		while (token)
		{
			if (!token_is_redir(token))
				return (1);
			token = token->next;
		}
	else
		while (token)
		{
			if (token->t_type == type)
				return (1);
			token = token->next;
		}
	return (0);	
}

t_ast	*parser(t_token **token, t_env *env, int *heredocs, t_shell *sh)
{
	int		type;
	t_token	*prev;
	t_token	*next;
	
	if (ft_lstfind(*token, PIPE))
	{
		prev = get_previous_pipe(*token);
		next = get_next_pipe(*token, sh);
		return (pipe_node(parser(&prev, env, heredocs, sh),
				parser(&next, env, heredocs, sh), token));
	}
	if (ft_lstfind(*token, REDIR))
	{
		prev = get_previous_redir(*token);
		return (redir_node(get_file_type(*token, &type, heredocs),
				parser(&prev, env, heredocs, sh), type, token));
	}
	if (ft_lstfind(*token, WORD))
		return (cmd_node(get_arg(*token), env, token));
	// ft_lstclear(token, &free);
    // ft_lstclear(&sh->token, &free);
	return (NULL);
}

//////////////AST PRINTER///////////////////////////////////

// Helper function to print indentation based on tree level
void print_indent(int level)
{
    for (int i = 0; i < level; i++)
        printf("    ");
}

// AST printer for t_cmd nodes
void print_cmd(t_cmd *cmd, int level)
{
    print_indent(level);
    printf("CMD: ");
    for (int i = 0; cmd->arg[i]; i++)
        printf("%s ", cmd->arg[i]);
    printf("\n");
}

// AST printer for t_redir nodes
void print_redir(t_redir *redir, int level)
{
    print_indent(level);
    if (redir->type == INPUT)
        printf("INPUT REDIR: %s\n", redir->file);
    else if (redir->type == APPEND)
        printf("APPEND OUTPUT: %s\n", redir->file);
    else if (redir->type == TRUNC)
        printf("OUTPUT REDIR: %s\n", redir->file);
    else if (redir->type == HEREDOC)
        printf("HEREDOC: %s\n", redir->file);

    // Recursively print the command inside the redirection
    ast_printer(redir->cmd, level + 1);
}

// AST printer for t_pipe nodes
void print_pipe(t_pipe *pipe_node, int level)
{
    print_indent(level);
    printf("PIPE:\n");

    // Print the left and right sides of the pipe
    print_indent(level + 1);
    printf("LEFT:\n");
    ast_printer(pipe_node->left, level + 2);

    print_indent(level + 1);
    printf("RIGHT:\n");
    ast_printer(pipe_node->right, level + 2);
}

// Main recursive AST printer
void ast_printer(t_ast *node, int level)
{
    if (!node)
        return;
    switch (node->type)
    {
    case CMD:
        print_cmd((t_cmd *)node, level);
        break;
    case INPUT:
    case APPEND:
    case TRUNC:
    case HEREDOC:
        print_redir((t_redir *)node, level);
        break;
    case PIPE:
        print_pipe((t_pipe *)node, level);
        break;
    default:
        print_indent(level);
        printf("Unknown node type\n");
    }
}
/////////////////////////////////////////
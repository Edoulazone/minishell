/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:31:15 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/02 11:32:19 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_pipe(t_ast *node, void (*ft_free_ast)(t_ast *))
{
	t_pipe *pipe = (t_pipe *)node;
	ft_free_ast(pipe->left);
	ft_free_ast(pipe->right);
	free(pipe);
}

void	ft_free_redir(t_ast *node, void (*ft_free_ast)(t_ast *))
{
	t_redir	*redir = (t_redir*)node;
	ft_free_ast(redir->cmd);
	free(redir->file);
	free(redir);
}
void	ft_freeargv(char **argv)
{
	int	i;

	i = 0;
	if (argv == NULL)
		return ;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	ft_free_cmd(t_ast *node)
{
	t_cmd	*cmd= (t_cmd*)node;
	ft_freeargv(cmd->arg);
	//free_env(*(cmd->g_env));
	free(cmd);
}

void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	if (node->type == PIPE)
		return(ft_free_pipe(node, &free_ast));
	if (node->type == INPUT
		|| node->type == APPEND
		|| node->type == TRUNC
		|| node->type == HEREDOC)
		return(ft_free_redir(node, &free_ast));
	if(node->type == CMD)
		return (ft_free_cmd(node));
}

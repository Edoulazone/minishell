/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:02:16 by eschmitz          #+#    #+#             */
/*   Updated: 2024/11/21 15:41:56 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_command(char **command)
{
    int i;

    i = 0;
    if (command)
    {
        while (command[i])
            free(command[i++]);
        free(command);
        command = NULL;
    }
}

void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	if (node->value)
		free_command(node->value);
    if (node->left)
        free_ast(node->left);
    if (node->right)
        free_ast(node->right);
    free(node);
    node = NULL;
}

void    free_token(t_token *token)
{
    t_token *temp;
    
    while (token)
    {
        temp = token;
        token = token->next;
        free(temp->content);
        free(temp);
    }
}

void    ft_free(t_shell *sh)
{
    if (sh->token)
    {
        free_token(sh->token);
        sh->token = NULL;
    }
    if (sh->command)
    {
        free(sh->command);
        sh->command = NULL;
    }
}

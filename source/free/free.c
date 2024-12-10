/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:02:16 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/10 16:35:59 by eschmitz         ###   ########.fr       */
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

void    free_token(t_token *token)
{
    t_token *temp;
    
    while (token)
    {
        if (token->next)
            token = token->next;
        temp = token;
        token = token->next;
        if (temp->content)
            free(temp->content);
        if (temp)
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

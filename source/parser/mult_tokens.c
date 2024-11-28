/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:22:48 by eschmitz          #+#    #+#             */
/*   Updated: 2024/11/27 11:02:58 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verif_pipes(t_token *temp)
{
	int	count;

	count = 0;
	while (temp && temp->t_type == PIPE)
	{
		temp = temp->next;
		count++;
		if (count == 3)
			return (ft_error("ERROR PIPE\n", 0, 0));
	}
	if (count > 1)
		return (ft_error("ERROR PIPE\n", 0, 0));
	return (0);
}

int	verif_right(t_token *temp)
{
	int	 count;

	count = 0;
	while (temp->content[count] == '>' && count <= 4)
		count++;
	if (count == 4)
		return (ft_error("ERROR PIPE\n", 0, 0));
	if (count == 3)
		return (ft_error("ERROR PIPE\n", 0, 0));
	return (0);
}

int	verif_left(t_token *temp)
{
	int	 count;

	count = 0;
	while (temp->content[count] == '<' && count <= 4)
		count++;
	if (count == 4)
		return (ft_error("ERROR PIPE\n", 0, 0));
	if (count == 3)
		return (ft_error("ERROR PIPE\n", 0, 0));
	return (0);
}

int	verif_tokens(t_shell *sh, t_token *token)
{
	int		verif;
	t_token	*temp;

	temp = token;
	verif = 0;
	while (temp)
	{
		if (temp->t_type == PIPE)
			verif += verif_pipes(temp);
		if (temp->t_type == CMD && temp->content[0] == '>')
			verif += verif_right(temp);
		if (temp->t_type == CMD && temp->content[0] == '<')
			verif += verif_left(temp);
		if (verif != 0)
		{
			sh->exit_status = 258;
			return (verif);
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

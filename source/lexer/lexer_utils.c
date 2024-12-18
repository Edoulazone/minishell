/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:57:51 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/13 15:47:38 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_meta(char c, int *sqs, int *dqs)
{
	if (*sqs || *dqs)
		return (0);
	if (c == 32 || c == 9)
		return (2);
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	check_qs(int sqs, int dqs, t_token **tokens)
{
	if (sqs || dqs)
	{
		ft_lstclear(tokens, &free);
		ft_error("syntax error: quote not closed\n", 0, 0);
		return (1);
	}
	return (0);
}

void	new_qs(char c, int *sqs, int *dqs)
{
	if (c == '\'')
	{
		if (!(*dqs))
		{
			if (!(*sqs))
				*sqs = 1;
			else
				*sqs = 0;
		}
	}
	if (c == '\"')
	{
		if (!(*sqs))
		{
			if (!(*dqs))
				*dqs = 1;
			else
				*dqs = 0;
		}
	}
}

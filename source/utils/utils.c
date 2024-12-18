/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:17:01 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/10 18:56:21 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_append(t_token *token, char *content, int type)
{
	while (token && (token)->next)
	{
		token = (token)->next;
	}
	if (token == NULL)
	{
		(token)->content = content;
		(token)->t_type = type;
		(token)->next = NULL;
	}
	return ;
}

int	countheredocs(t_token *token)
{
	int		nbr_heredocs;

	nbr_heredocs = 0;
	while (token)
	{
		if (token->t_type == HEREDOC)
			nbr_heredocs ++;
		token = token->next;
	}
	return (nbr_heredocs);
}

int	ft_lstsize(t_token *lst)
{
	int		size;
	t_token	*lst_dup;

	if (lst)
	{
		size = 1;
		lst_dup = lst;
	}
	else
		return (0);
	while (lst_dup->next)
	{
		size++;
		lst_dup = lst_dup->next;
	}
	return (size);
}

int	is_quote(char c)
{
	if (c == '\"' || c == '\'')
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

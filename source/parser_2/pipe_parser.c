/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:48:01 by eschmitz          #+#    #+#             */
/*   Updated: 2024/11/28 14:07:42 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*pipe_node(t_ast *left, t_ast *right, t_token **token)
{
	t_pipe	*pipe;

	pipe = malloc(sizeof(t_pipe));
	if (!pipe)
		return (NULL);
	pipe->type = PIPE;
	pipe->left = left;
	pipe->right = right;
	ft_lstclear(token, &free);
	return ((t_ast *)pipe);
}

t_token	*get_previous_pipe(t_token *token)
{
	t_token	*prev;
	
	prev = NULL;
	while (token && token->t_type != PIPE)
	{
		ft_lstadd_back(&prev, ft_lstnew(ft_strdup(token->content),
				token->t_type));
		token = token->next;
	}
	return (prev);
}

t_token	*get_next_pipe(t_token *token)
{
	t_token	*next;
	
	next = NULL;
	while (token && token->t_type != PIPE)
		token = token->next;
	token = token->next;
	if (!token)
	{
		lex(readline("> "), &next);
		return (next);
	}
	while (token)
	{
		ft_lstadd_back(&next, ft_lstnew(ft_strdup(token->content),
				token->t_type));
		token = token->next;
	}
	return (next);
}

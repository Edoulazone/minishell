/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:24:35 by eschmitz          #+#    #+#             */
/*   Updated: 2024/11/28 13:47:05 by eschmitz         ###   ########.fr       */
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
				return (EXIT_SUCCESS);
			token = token->next;
		}
	else
		while (token)
		{
			if (token->t_type == type)
				return (EXIT_SUCCESS);
			token = token->next;
		}
	return (EXIT_FAILURE);	
}

t_ast	*parser(t_token **token, t_env *env, int *heredocs)
{
	int		type;
	t_token	*prev;
	t_token	*next;
	
	if (!ft_lstfind(*token, PIPE))
	{
		prev = get_previous_pipe(*token);
		next = get_next_pipe(*token);
		return (pipe_node(parser(&prev, env, heredocs),
				parser(&next, env, heredocs), token));
	}
	if (!ft_lstfind(*token, REDIR))
	{
		prev = get_previous_redir(*token);
		return (redir_node(get_file_type(*token, &type, heredocs, env),
				parser(&prev, env, heredocs), type, token));
	}
	if (!ft_lstfind(*token, WORD))
		return (cmd_node(get_arg(*token), env, token));
	ft_lstclear(token, &free);
	return (NULL);
}

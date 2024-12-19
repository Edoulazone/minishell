/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:24:35 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/18 18:44:49 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstfind(t_token *token, int type)
{
	if (!token)
		return (EXIT_FAILURE);
	if (type == REDIR)
	{
		while (token)
		{
			if (!token_is_redir(token))
				return (1);
			token = token->next;
		}
	}
	else
	{
		while (token)
		{
			if (token->t_type == type)
				return (1);
			token = token->next;
		}
	}
	return (0);
}

void	pipe_error(void)
{
	my_write(2, "minishell: syntax error: unexpected end of file\n", 3);
}

t_ast	*parser(t_token **token, t_env *env, int *heredocs, t_shell *sh)
{
	int		type;
	t_token	*prev;
	t_token	*next;

	if (ft_lstfind(*token, PIPE))
	{
		prev = get_previous_pipe(*token);
		next = get_next_pipe(*token, prev);
		if (!prev || !next)
			return (pipe_error(), pipe_node(NULL, NULL));
		return (pipe_node(parser(&prev, env, heredocs, sh),
				parser(&next, env, heredocs, sh)));
	}
	if (ft_lstfind(*token, REDIR))
	{
		prev = get_previous_redir(*token);
		if (!prev)
			return (redir_node(get_file_type(*token, &type, heredocs),
					NULL, type));
		return (redir_node(get_file_type(*token, &type, heredocs),
				parser(&prev, env, heredocs, sh), type));
	}
	if (ft_lstfind(*token, WORD))
		return (cmd_node(get_arg(*token), env));
	return (NULL);
}

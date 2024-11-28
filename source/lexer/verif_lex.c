/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_lex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:30:01 by eschmitz          #+#    #+#             */
/*   Updated: 2024/11/27 10:19:39 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_lex(char *str, char *t_content)
{
	write(2, str, ft_strlen(str));
	write(2, "`", 1);
	write(2, t_content, ft_strlen(t_content));
	write(2, "\'", 1);
	write(2, "\n", 1);
	return (1);
}

int	verif_lex(t_shell *sh, t_token *token)
{
	if (token && token->t_type == PIPE)
		return (sh->exit_status = 258,
			error_lex("bash: syntax error near unexpected token",
				token->content));
	while (token)
	{
		if (token->t_type >= INPUT && token->t_type <= APPEND)
		{
			if (!token->next)
			{
				sh->exit_status = 258;
				return (error_lex("bash: syntax error near unexpected token",
						"newline"));
			}
			if (token->next->t_type != WORD)
			{
				sh->exit_status = 258;
				return (error_lex("bash: syntax error near unexpected token",
						token->next->content));
			}
		}
		token = token->next;
	}
	return (0);
}
 
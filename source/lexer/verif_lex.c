/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_lex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:30:01 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/04 14:13:01 by eschmitz         ###   ########.fr       */
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

int	verif_lex(t_shell *sh)
{
	t_token	*temp;

	temp = sh->token;
	if (temp && temp->t_type == PIPE)
		return (sh->exit_status = 258,
			error_lex("bash: syntax error near unexpected token",
				temp->content));
	while (temp)
	{
		if (temp->t_type >= INPUT && temp->t_type <= APPEND)
		{
			if (!temp->next)
				return (sh->exit_status = 258,
					error_lex("bash: syntax error near unexpected token",
					"newline"));
			if (temp->next->t_type != WORD)
				return (sh->exit_status = 258,
						error_lex("bash: syntax error near unexpected token",
						temp->next->content));
		}
		temp = temp->next;
	}
	return (0);
}
 
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_lex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:30:01 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/16 14:06:45 by eschmitz         ###   ########.fr       */
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

int	on_reduit_la_longueur_de_verif_lex(t_token *temp)
{
	if (!temp->next)
		return (g_exit_status = 258,
			error_lex("bash: syntax error near unexpected token",
				"newline"));
	if (temp->next->t_type != WORD)
		return (g_exit_status = 258,
			error_lex("bash: syntax error near unexpected token",
				temp->next->content));
	return (0);
}

int	verif_lex(t_token *token)
{
	t_token	*temp;

	if (!token)
		return (1);
	temp = token;
	if (token->content && token->content[0] == '\0')
		return (1);
	if (temp && temp->t_type == PIPE)
		return (g_exit_status = 258,
			error_lex("bash: syntax error near unexpected token",
				temp->content));
	while (temp)
	{
		if (temp->t_type >= INPUT && temp->t_type <= APPEND)
			return (on_reduit_la_longueur_de_verif_lex(temp));
		if (temp->t_type == PIPE)
			if (temp->next && temp->next->t_type == PIPE)
				return (g_exit_status = 1, error_lex("NO BONUS ", "|| or &&"));
		if (!ft_strcmp(temp->content, "||") || !ft_strcmp(temp->content, "&&"))
			return (g_exit_status = 1, error_lex("NO BONUS ", "|| or &&"));
		temp = temp->next;
	}
	return (0);
}

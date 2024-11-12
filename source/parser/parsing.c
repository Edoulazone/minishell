/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:14:51 by eschmitz          #+#    #+#             */
/*   Updated: 2024/11/12 18:09:53 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Vérifie si c'est une commande ou un argument
int	is_command(int type)
{
	if (type == CMD || type == ARG)
		return (0);
	return (1);
}

//Vérifie si les redirections sont possiblement faisables
int	verif_redirect(t_token *current_t)
{
	if (current_t->next == NULL || is_command(current_t->next->t_type) == 1)
		return (ft_error("ERROR PIPE\n", 0, 0));
	return (0);
}

//Vérifie le type et l'existence des tokens
int	verif_token(t_shell *sh)
{
	int		verif;
	t_token	*temp;

	verif = 0;
	while (sh->token)
	{
		printf("%s\n", sh->token->content);
		sh->token = sh->token->next;
	}
	temp = sh->token;
	printf("Nice\n");
	if (temp->t_type == PIPE && temp->next == NULL)
		return (ft_error(SYNTAX_ERROR, '|', 1));
	printf("Nice\n");
	while (temp != NULL)
	{
		if (temp->t_type == TRUNC || temp->t_type == INPUT
			|| temp->t_type == APPEND || temp->t_type == HEREDOC)
			verif = verif_redirect(temp);
		temp = temp->next;
		if (verif != 0)
			return (verif);
	}
	return (verif);
}

//Gère le déroulement général du parsing
int	parsing(t_shell *sh)
{
	if (verif_token(sh) > 0)
		return (1);
	sh->ast = make_ast(sh->token);
	if (!sh->ast)
		return (1);
	return (0);
}

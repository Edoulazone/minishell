/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:21:05 by eschmitz          #+#    #+#             */
/*   Updated: 2024/10/28 14:41:47 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Récupère les tokens pour extraire les commandes et les retourner sous forme de tableau de strings
char	**get_command(t_token *token)
{
	int		count;
	int		i;
	char	**command;

	count = 0;
	i = -1;
	while (token && is_command(token->t_type) == 0 && count++ <= 1000000)
		token = token->next;
	command = (char **)malloc(sizeof(char *) * (count + 1));
	if (!command)
		return (NULL);
	while (token && is_command(token->t_type) == 0)
	{
		command[++i] = ft_strdup(token->str);
		token = token->next;
	}
	command[i] = NULL;
	return (command);
}

// Crée un node à partir d'une valeur et d'un type reçus
t_ast	*make_ast_node(char	**value, int type)
{
	t_ast	*node;
	
	node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->value = value;
	node->n_type = type;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

//Crée l'AST grâce aux jetons reçus en paramètre
t_ast	*make_ast(t_token *tokens)
{
	t_token	*current;
	t_ast	*origin;

	if (!tokens)
		return (NULL);
	origin = NULL;
	origin = ast_priority(tokens, origin);
	if (origin)
		return (origin);
	current = tokens;
	while (current && (is_command(current->t_type) == 0
			|| current->t_type == PIPE || current->t_type == HEREDOC))
		current = current->next;
	if (current && is_command(current->t_type) == 1 && current->t_type != PIPE
		&& current->t_type != HEREDOC)
		return (build_left_pipe(tokens)); // fonction à faire
	current = tokens;
	if (is_command(current->t_type) == 0)
	{
		origin = make_ast_node(get_command(current), CMD); // fonction à faire
		while (current && is_command(current->t_type) == 0)
			current = current->next;
	}
	return (origin);
}

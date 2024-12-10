/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:51:47 by eschmitz          #+#    #+#             */
/*   Updated: 2024/11/28 17:38:45 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// // Construit la structure à gauche d'un pipe
// t_ast	*pipe_left(t_token *tokens)
// {
// 	t_token	*current;
// 	t_ast	*new_node;
// 	t_ast	*origin;

// 	origin = NULL;
// 	new_node = NULL;
// 	current = tokens;
// 	while (current && current->t_type != PIPE && current->t_type != HEREDOC)
// 	{
// 		if (is_command(current->t_type) == 1)
// 		{
// 			new_node = make_ast_node(NULL, current->t_type);
// 			new_node->left = origin;
// 			current = current->next;
// 			new_node->right = pipe_left(current);
// 			return (new_node);
// 		}
// 		else
// 		{
// 			origin = make_ast_node(get_command(current), CMD);
// 			while (current && is_command(current->t_type) == 0)
// 				current = current->next;	
// 		}
// 	}
// 	return (origin);
// }

// // Construit la structure à gauche d'un heredoc
// t_ast	*heredoc_left(t_token *tokens)
// {
// 	t_token	*current;
// 	t_ast	*new_node;
// 	t_ast	*origin;

// 	origin = NULL;
// 	new_node = NULL;
// 	current = tokens;
// 	while (current && current->t_type != HEREDOC)
// 	{
// 		if (is_command(current->t_type) == 1)
// 		{
// 			new_node = make_ast_node(NULL, current->t_type);
// 			new_node->left = origin;
// 			current = current->next;
// 			new_node->right = heredoc_left(current);
// 			return (new_node);
// 		}
// 		else
// 		{
// 			origin = make_ast_node(get_command(current), CMD);
// 			while (current && is_command(current->t_type) == 0)
// 				current = current->next;	
// 		}
// 	}
// 	return (origin);
// }

// // Vérifie la présence de pipes et retourne leur position s'il y en a
// t_ast	*check_ast_pipe(t_token *tokens, t_ast *origin)
// {
// 	t_token	*current;

// 	current = tokens;
// 	origin = NULL;
// 	while (current && current->t_type != PIPE)
// 		current = current->next;
// 	if (current && current->t_type == PIPE)
// 	{
// 		origin = make_ast_node(NULL, PIPE);
// 		origin->left = pipe_left(tokens);
// 		origin->right = make_ast(current->next);
// 		return (origin);
// 	}
// 	return (NULL);
// }

// // Vérifie la présence de heredocs et retourne leur position s'il y en a
// t_ast	*check_ast_heredoc(t_token *tokens, t_ast *origin)
// {
// 	t_token	*current;

// 	current = tokens;
// 	origin = NULL;
// 	while (current && current->t_type != HEREDOC)
// 		current = current->next;
// 	if (current && current->t_type == HEREDOC)
// 	{
// 		origin = make_ast_node(NULL, HEREDOC);
// 		origin->left = heredoc_left(tokens);
// 		origin->right = make_ast(current->next);
// 		return (origin);
// 	}
// 	return (NULL);
// }

// // Vérifie s'il y a des heredocs et des pipes pour placer l''origine et respecter l'ordre de priorité des opéraations
// t_ast	*ast_priority(t_token *tokens, t_ast *origin)
// {
// 	origin = NULL;
// 	origin = check_ast_heredoc(tokens, origin);
// 	if (origin)
// 		return (origin);
// 	origin = check_ast_pipe(tokens, origin);
// 	if (origin)
// 		return (origin);
// 	return (NULL);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:22:05 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/18 14:37:51 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_is_redir(t_token *token)
{
	if (!token)
		return (1);
	if (token->t_type == INPUT || token->t_type == HEREDOC)
		return (0);
	if (token->t_type == APPEND || token->t_type == TRUNC)
		return (0);
	return (1);
}

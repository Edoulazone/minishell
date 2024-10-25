/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:29:57 by eschmitz          #+#    #+#             */
/*   Updated: 2024/10/17 16:08:54 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_type(char *str, int check)
{
	if (str[0] == '|')
	{
		if (ft_strlen(str) == 1)
			return (1);
	}
	return (0);
}

int	input_heredoc_type(char *str, int check)
{
	if (str[0] == '<')
	{
		if (check == 1)
			return (1 + input_type(&str[1]));
		if (ft_strlen(str) == 1)
			return (0);
	}
	return (0);
}

int	trunc_append_type(char *str, int check)
{
	if (str[0] == '>')
	{
		if (ft_strlen(str) == 1)
			return (1 + trunc_type(&str[1]));
	}
	return (0);
}

int	is_delimiter(char c)
{
	if (c == ';' || c == '|' || c == '&' || c == '<' || c == '>'
		|| c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

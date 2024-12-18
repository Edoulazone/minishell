/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:42:14 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/10 14:27:08 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exp_sq_heredoc(char *copy, int *i, char *str)
{
	int		start;
	char	*expand;

	*i += 1;
	start = *i;
	while (str[*i] && str[*i] != '\'')
		*i += 1;
	expand = ft_substr(str, start, *i - start);
	copy = ft_strjoin(copy, expand);
	*i += 1;
	return (copy);
}

static char	*exp_dq_heredoc(char *copy, int *i, char *str)
{
	int		start;
	char	*expand;

	*i += 1;
	start = *i;
	while (str[*i] && str[*i] != '\"')
		*i += 1;
	expand = ft_substr(str, start, *i - start);
	copy = ft_strjoin(copy, expand);
	*i += 1;
	return (copy);
}

char	*expand_heredoc(char *str)
{
	int		i;
	char	*copy;

	i = 0;
	copy = ft_strdup("");
	while (str && str[i])
	{
		if (str[i] == '\"')
			copy = exp_dq_heredoc(copy, &i, str);
		else if (str[i] == '\'')
			copy = exp_sq_heredoc(copy, &i, str);
		else
		{
			copy = join_char(copy, str[i]);
			i++;
		}
	}
	return (copy);
}

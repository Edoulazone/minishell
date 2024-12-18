/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:57:49 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/11 15:33:46 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_sq(char *copy, char *str, int *i)
{
	int		start;
	char	*expand;

	*i += 1;
	start = *i;
	while (str[*i] && str[*i] != '\'')
		*i += 1;
	expand = ft_substr(str, start, *i - start);
	copy = ft_strjoin(copy, expand);
	free(expand);
	*i += 1;
	return (copy);
}

char	*expand_dq(t_shell *sh, char *copy, char *str, int *i)
{
	int	start;

	*i += 1;
	start = *i;
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '$')
			copy = exp_env_var(sh, copy, str, i);
		else
		{
			if (str[*i - 1] && str[*i - 1] == '$')
				copy = join_char(copy, '$');
			copy = join_char(copy, str[*i]);
			*i += 1;
		}
	}
	*i += 1;
	return (copy);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:22:50 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/10 18:32:10 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*normal_case(char *copy, char *str, int *i)
{
	if (str[(*i) - 1] && str[(*i) - 1] == '$')
		copy = join_char(copy, '$');
	copy = join_char(copy, str[*i]);
	*i += 1;
	return (copy);
}

char	*join_char(char *str, char c)
{
	int		i;
	int		len;
	
	i = -1;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	str = ft_realloc(str, len + 2);
	str[len] = c;
	str[len + 1] = '\0';
	return (str);
}

static char	*dispatch_quotes(t_shell *sh, char *copy, char *str, int *i)
{
	if (str[*i] == '\"')
		copy = expand_dq(sh, copy, str, i);
	else if (str[*i] == '\'')
		copy = expand_sq(copy, str, i);
	return (copy);
}

static char	*dispatch_expand(t_shell *sh, char *copy, char *str, int i)
{
	while (str && str[i])
	{
		if (is_quote(str[i]))
			copy = dispatch_quotes(sh, copy, str, &i);
		else if (str[i] == '$')
		{
			if (str[i] == '$' && !str[i + 1])
			{
				copy = join_char(copy, str[i]);
				break ;
			}
			if (str[i] == '$' && ft_isdigit((int)str[i + 1]))
			{
				i += 2;
				continue ;
			}
			copy = exp_env_var(sh, copy, str, &i);
		}
		else
			copy = normal_case(copy, str, &i);
	}	
	return (copy);
}

char	*get_word(t_shell *sh, char *str)
{
	int		i;
	char	*copy;
	t_env	*home;
	
	i = 0;
	copy = ft_strdup("");
	if (!ft_strncmp("~", str, 1))
	{
		home = get_node(sh->env, "HOME");
		copy = ft_strjoin(copy, home->content);
		i++;
	}
	copy = dispatch_expand(sh, copy, str, i);
	return (copy);
}

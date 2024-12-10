/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:43:15 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/10 17:29:31 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_shell *sh, t_env_exp *env)
{
	int		i;
	int		len;
	char	*str;
	t_env	*current;

	i = 0;
	len = ft_strlen(env->var);
	current = sh->env;
	while (current && ft_strcmp(env->var, current->value))
		current = current->next;
	if (!current)
		return (NULL);
	str = current->value;
	env->var_len = ft_strlen(str);
	if (len != env->var_len)
		return (NULL);
	env->expand = current->content;
	return ("");
}

int	check_special(char c)
{
	return ((c >= 33 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 94)
		|| c == 96 || (c >= 123 && c <= 126));
}

int	check_whitespace(char *str, int i)
{
	return (str[i] == ' ' || (str[i] >= (int)9 && str[i] <= 13));
}

char	*handle_env_var(t_shell *sh, char *str, int i)
{
	char		*check;
	t_env_exp	*env;
	
	env = sh->env_exp;
	if (!str[i + 1])
		return (NULL);
	i++;
	env->end = i;
	env->start = i;
	while (str[i] && !check_whitespace(str, i)
			&& !check_special(str[i]) && !is_quote(str[i]))
	{
		i++;
		env->end++;
	}
	env->var = ft_substr(str, env->start, env->end - env->start);
	check = get_env(sh, env);
	if (!check)
		return (NULL);
	free(env->var);
	return (env->expand);
}

char	*exp_env_var(t_shell *sh, char *copy, char *str, int *i)
{
	char	*expand;

	if (str[*i + 1] == '?')
	{
		copy = ft_strjoin(copy, ft_itoa(sh->exit_status));
		*i += 2;
		return (copy);
	}
	expand = handle_env_var(sh, str, *i);
	if (!expand)
		*i += sh->env_exp->end - sh->env_exp->start + 1;
	else
	{
		// write(2, "Check\n", 6);
		*i += sh->env_exp->end - sh->env_exp->start + 1;
		copy = ft_strjoin(copy, sh->env_exp->expand);
	}
	return (copy);
}

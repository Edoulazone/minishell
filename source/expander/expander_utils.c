/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:14:20 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/16 15:47:25 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_node(t_env *env, char *var)
{
	t_env	*node;

	node = env;
	while (node && ft_strncmp(node->value, var, INT_MAX))
		node = node->next;
	if (node && !ft_strncmp(node->value, var, INT_MAX))
		return (node);
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	if (!s1 || !s2)
		return (0);
	while (i < n)
	{
		if (s1[i] != s2[i] || s1[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

t_token	*init_token(void)
{
	t_token	*list;

	list = malloc(sizeof(t_token));
	if (!list)
		return (NULL);
	list->content = NULL;
	list->t_type = 0;
	list->next = NULL;
	return (list);
}

t_env_exp	*init_var_exp(void)
{
	t_env_exp	*env;

	env = malloc(sizeof(t_env_exp));
	if (!env)
		return (NULL);
	env->end = 0;
	env->sub = 0;
	env->start = 0;
	env->var = NULL;
	env->var_len = 0;
	env->expand = NULL;
	return (env);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*new_s;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s) || ft_strlen(s) == 0)
		len = 0;
	if (start < ft_strlen(s) && len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	new_s = (char *)malloc((len + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	while (s[start + i] && i < len)
	{
		new_s[i] = s[start + i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

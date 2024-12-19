/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:25:17 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/19 13:13:04 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*special_create_env(void)
{
	t_env	*list;
	t_env	*save;

	list = (t_env *)safe_malloc(sizeof(t_env));
	save = list;
	list->value = safe_strdup("OLDPWD");
	list->content = NULL;
	list->next = (t_env *)safe_malloc(sizeof(t_env));
	list = list->next;
	list->value = safe_strdup("PWD");
	list->content = safe_strdup("/Users/eschmitz");
	list->next = (t_env *)safe_malloc(sizeof(t_env));
	list = list->next;
	list->value = safe_strdup("SHLVL");
	list->content = safe_strdup("1");
	list->next = (t_env *)safe_malloc(sizeof(t_env));
	list = list->next;
	list->value = safe_strdup("_");
	list->content = safe_strdup("/usr/bin/env");
	return (save);
}

void	*safe_malloc(unsigned int size)
{
	void	*result;

	result = malloc(size);
	if (!result)
		exit(EXIT_FAILURE);
	return (result);
}

char	*safe_strdup(char *str)
{
	char	*result;

	result = ft_strdup(str);
	if (!result)
		exit(EXIT_FAILURE);
	return (result);
}

void	free_split(char **mem)
{
	int	i;

	i = 0;
	while (mem[i] != NULL)
	{
		free(mem[i]);
		i++;
	}
	free(mem);
}

char	*safe_strjoin(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (!result)
		exit(EXIT_FAILURE);
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:09:31 by gnyssens          #+#    #+#             */
/*   Updated: 2024/10/21 17:36:29 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	length_untill_c(char *str, char c)
{
	int len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	if (str[len] != c) // == probleme !
		return (0);
	return (len);
}

char	*strdup_until_c(char *str, char c)
{
	int		equal;
	int		len;
	char	*result;

	equal = 0;
	len = length_untill_c(str, c);
	if (str[len] == c) //sinon ya un probleme en vrai, pas de '=' dans un env...
	{
		equal = 1;
		str[len] = '\0';
	}
	result = safe_strdup(str);
	str[len] = c;
	return (result);
}

t_env	*init_env_list(char **env)
{
	int		i;
	t_env	*head;
	t_env	*current;

	if (!env)
		return (NULL);
	head = (t_env *)safe_malloc(sizeof(t_env));
	i = 0;
	head->value = strdup_until_c(env[i], '=');
	head->content = safe_strdup(env[i] + length_untill_c(env[i], '=') + 1); //pr copier tout ce qu'il y a après '='
	current = head;
	while (env[++i])
	{
		if (env[i + 1])
			current->next = (t_env *)safe_malloc(sizeof(t_env));
		else
			current->next = NULL; //quand cest le dernier node, je mets next a NULL sans mallocquer
		current = current->next;
		if (current)
		{
			current->value = strdup_until_c(env[i], '=');
			current->content = safe_strdup(env[i] + length_untill_c(env[i], '=') + 1);
		}
	}
	return (head);
}

void	ft_env(t_env *head)
{
	t_env	*current;

	current = head;
	while (current != NULL)
	{
		if (current->value && current->content)
		{
			write(1, (current->value), ft_strlen(current->value));
			write(1, "=", 1);
			write(1, (current->content), ft_strlen(current->content));
			write(1, "\n", 1);
		}
		current = current->next;
	}
}

void	free_env_list(t_env *head)
{
	t_env	*current;

	current = head;
	while (current)
	{
		if (current->content)
			free(current->content);
		if (current->value)
			free(current->value);
		current = current->next;
	}
	current = head;
	while (head)
	{
		head = current->next;
		free(current);
		current = head;
	}
}

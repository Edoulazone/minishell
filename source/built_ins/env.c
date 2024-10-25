/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:09:31 by gnyssens          #+#    #+#             */
/*   Updated: 2024/10/08 18:22:46 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//verifiee dans goinfre, elle marche
t_list	*init_env_list(char **env)
{
	int		i;
	t_list	*head;
	t_list	*current;

	if (!env)
		return (NULL);
	head = (t_list *)malloc(sizeof(t_list));
	if (!head)
		return (NULL);
	i = 0;
	head->content = (char *)ft_strdup(env[i]); //au lieu de proteger je ferai un safe_strdup plus tard
	current = head;
	while (env[++i])
	{
		if (env[i + 1])
			current->next = (t_list *)malloc(sizeof(t_list));
		else
			current->next = NULL; //quand cest le dernier node, je mets next a NULL sans mallocquer
		if (!(current->next) && env[i + 1])
			return (NULL); //faudra free etc.
		if (current->next)
			current->next->content = (char *)ft_strdup(env[i]);
		current = current->next;
	}
	return (head);
}

void	ft_env(t_list *head)
{
	t_list	*current;

	current = head;
	while (current != NULL)
	{
		write(1, (char *)(current->content), ft_strlen((char *)(current->content)));
		write(1, "\n", 1);
		current = current->next;
	}
}

void	free_env_list(t_list *head)
{
	t_list	*current;

	current = head;
	while (current)
	{
		if (current->content)
			free(current->content);
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

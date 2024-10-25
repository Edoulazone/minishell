/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:49:14 by eschmitz          #+#    #+#             */
/*   Updated: 2024/10/08 18:43:09 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Créer un noeud avec une variable d'environnement
t_env	*create_env_node(char *var)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->content = ft_ssearch(var, '=', 1);
	new_node->value = ft_ssearch(var, '=', 0);
	if (new_node->value != NULL)
		new_node->type = 1;
	else
		new_node->type = 0;
	new_node->next = NULL;
	return (new_node);
}

//Ajouter une variable d'environnement sous forme de noeud à la liste
void	add_node(t_env **list, t_env *new_node)
{
	t_env	*temp;

	if (!new_node)
		return ;
	if (*list == NULL)
		list == new_node;
	else
	{
		temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

//Créer la liste de variables d'environnement
int	make_env(t_shell *sh, char **envp)
{
	t_env	*new_node;
	int		i;

	i = -1;
	while (envp[++i])
	{
		new_node = create_env_node(envp[i]);
		add_node(&sh->env, new_node);
	}
	i = 0;
	while (envp[i] != NULL)
		i++;
	sh->envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (1);
	i = -1;
	while (envp[++i] != NULL)
		sh->envp[i] = ft_strdup(envp[i]);
	sh->envp[i] = NULL;
	return (0);
}

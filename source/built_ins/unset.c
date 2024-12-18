/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:59:51 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/18 13:02:46 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_strcmp(char *env_str, char *check, char c)
{
	int	i;

	i = 0;
	while (env_str[i])
	{
		if (check[i] != env_str[i] && env_str[i] != c)
			return (1);
		if (env_str[i] == c && !check[i])
			return (write(1, "arg trouvé !\n", 14), 0);
		if (env_str[i] == c && check[i])
			return (1);
		i++;
	}
	return (1);
}

void	remove_env_node(t_env **head, char *check, t_env **first)
{
	t_env	*before_cut;
	t_env	*remove;

	before_cut = *head;
	if (ft_strcmp((*head)->value, check) == 0)
	{
		free((*head)->value);
		if ((*head)->content)
			free((*head)->content);
		(*head) = (*head)->next;
		*first = *head;
		return ;
	}
	(void)first;
	while (ft_strcmp(before_cut->next->value, check) != 0)
		before_cut = before_cut->next;
	remove = before_cut->next;
	free((remove->value));
	if (remove->content)
		free(remove->content);
	before_cut->next = remove->next;
	free(remove);
}

int	ft_unset(t_cmd *node, t_env **env)
{
	t_env	*first;
	t_env	*current;
	char	**args;
	int		i;

	first = *env;
	args = node->arg;
	if (!(args[1]))
		return (1);
	i = 1;
	current = *env;
	while (args[i])
	{
		if (ft_strcmp((current->value), args[i]) == 0)
		{
			remove_env_node(env, args[i], &first);
			i++;
			current = first;
		}
		current = current->next;
		if (current == NULL)
			break ;
	}
	g_exit_status = 0;
	return (0);
}

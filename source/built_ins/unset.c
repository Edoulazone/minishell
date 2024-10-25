/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:59:51 by gnyssens          #+#    #+#             */
/*   Updated: 2024/10/14 15:30:07 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks if 'check' is similar to env_str up untill the char c in env_str
// return (0) means it's found ! just like strcmp, 1 is not found
int	special_strcmp(char *env_str, char *check, char c)
{
	int	i;

	i = 0;
	while (env_str[i])
	{
		if (check[i] != env_str[i] && env_str[i] != c)
			return (1);
		if (env_str[i] == c && !check[i])
			return (write(1, "arg trouvé !\n", 14), 0); //this means it corresponds, and the path shall be removed
		if (env_str[i] == c && check[i])
			return (1);
		i++;
	}
	return (1);
}

//legerement redondante puisqu'elle doit re-checker special_strcmp
void	remove_env_node(t_list **head, char *check, t_list **first)
{
	t_list	*before_cut;
	t_list	*remove;

	before_cut = *head;
	if (special_strcmp((*head)->content, check, '=') == 0)
	{
		write(1, "argument is head's content !\n", 29);
		free((*head)->content);
		(*head) = (*head)->next;
		*first = *head;
		return ;
	}
	(void)first;
	while (special_strcmp(before_cut->next->content, check, '=') != 0)
		before_cut = before_cut->next;
	remove = before_cut->next;
	free((remove->content));
	before_cut->next = remove->next;
	free(remove);
	write(1, "now it should have been removed !\n", 34);
}

//ce sera sans doute pas un void, pr retourner 1 ou 0 pr succes/failure
void	ft_unset(t_ast_command *cmd, t_list **env)
{
	t_list	*first;
	t_list	*current;
	char	**args;
	int		i;

	first = *env;
	args = cmd->args;
	if (!(args[1]))
	{
		write(1, "no arguments for unset !\n", 25);
		return ;
	}
	i = 1;
	current = *env;
	while (args[i])
	{
		if (special_strcmp((char *)(current->content), args[i], '=') == 0)
		{
			write(1, "PATH FOUND\n", 11);
			remove_env_node(env, args[i], &first);
			i++;
			current = first;
		}
		current = current->next;
		if (current == NULL)
		{
			if (i == 1)
				write(1, "wrong argument, no such ENV variable\n", 37);
			break;
		}
	}
}

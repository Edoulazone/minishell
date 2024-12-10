/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:24:11 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/02 13:46:22 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// -n a le mm effet que -nnnn, d'ou la necessite pr cette fonction
bool only_n(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else
			return (false);
	}
	return (true);
}

//check si y'a '-n' apres 'echo'
bool	option_new_line(char **args, int *p)
{
	bool	result;

	result = false;
	while (args[*p] && args[*p][0] == '-')
	{
		if (args[*p][0] == '-' && only_n(args[*p]))
		{
			(*p) += 1; //augmente i de 1 pr skipper le '-n' a l'ecriture
			result = true;
		}
		else
			break;
	}
	return (result);
}

void	ft_echo(t_cmd *node)
{
	bool	new_line;
	int		i;
	char	**args;

	i = 1;
	new_line = option_new_line(node->arg, &i);
	args = node->arg;
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (new_line == false)
		write(1, "\n", 1);
}

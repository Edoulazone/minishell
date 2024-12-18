/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:24:11 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/17 17:34:37 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	only_n(char *str)
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

bool	option_new_line(char **args, int *p)
{
	bool	result;

	result = false;
	while (args[*p] && args[*p][0] == '-')
	{
		if (args[*p][0] == '-' && only_n(args[*p]))
		{
			(*p) += 1;
			result = true;
		}
		else
			break ;
	}
	return (result);
}

void	ft_echo(t_cmd *node)
{
	bool	new_line;
	int		i;
	char	**args;

	if (!(node->arg[1]))
	{
		write(1, "\n", 1);
		return ;
	}
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
	g_exit_status = 0;
}

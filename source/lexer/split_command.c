/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:04:42 by eschmitz          #+#    #+#             */
/*   Updated: 2024/10/22 12:26:53 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_index(char *str)
{
	int	i;
	
	i = 0;
	while (str[i] == ' ' && str[i] != '\0')
		i++;
	if (str[i] == '"')
	{
		i++;
		while (str[i] != '"')
			i++;
	}
	if (str[i] == "'")
	{
		i++;
		while (str[i] != "'")
			i++;
	}
	return (i);
}

int	number_elem(t_shell *sh, int count)
{
	int	i;
	int	temp;

	i = 0;
	while (sh->command[i] != '\0')
	{
		i += char_index(&sh->command[i]);
		if (sh->command[i] == '\0')
			return (count);
	}
}

int	make_elem(t_shell *sh, int count)
{
	t_elem	elem;

	elem.c = 0;
	while (elem.c < count)
	{
		elem.size = check_elem(sh, elem.c, 0);
	}
}

int	split_command(t_shell *sh)
{
	int	count;

	count = 0;
	count = number_elem(sh, count);
	if (count == 0)
		return (EXIT_FAILURE);
	sh->commands = malloc(sizeof(char *) * (count + 1));
	if (!sh->commands)
		return (EXIT_FAILURE);
	if (make_elem(sh, count) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

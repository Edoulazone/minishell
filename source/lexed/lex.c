/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:25:08 by eschmitz          #+#    #+#             */
/*   Updated: 2024/10/25 14:48:14 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_command(char *str, int origin, int index)
{
	char	*command;

	command = malloc(sizeof(char) * (index - origin + 2));
	if (!command)
		return (NULL);
	while (origin <= index)
		command[origin] = str[origin++];
	command[origin] = '\0';
	return (command);
}

int	is_meta(char c)
{
	if (c == '(' || c == ')' || c == 32 || c == '\n' || c == 9)
		return (1);
	if (c == ';' || c == '|' || c == '&' || c == '<' || c == '>')
		return (2);
	return (0);
}

int	command_loop(t_shell *sh, char *str)
{
	int	index;
	int	origin;
	int	c;

	index = 0;
	origin = 0;
	c = 0;
	while (str && str[origin])
	{
		while (!is_meta(str[index]))
			index++;
		if (index > origin)
			sh->commands[c++] = make_command(str, origin, index);
		if (is_meta(str[index]) == 1)
			sh->commands[c++] = make_command(str, origin++, index++);
		if (is_meta(str[index]) == 2)
		{
			while (str[index] == str[index + 1])
				index++;
			sh->commands[c++] = make_command(str, origin, index);
		}
		origin = index;
	}
	return (0);
}

int	count_commands(char *str)
{
	int	i;
	int	count;
	int	flag;

	count = 0;
	i = 0;
	while (str && str[i])
	{
		flag = 0;
		while (!is_meta(str[i++]))
			flag = 1;
		if (flag == 1)
			count++;
		while (is_meta(str[i++]) == 1)
			count++;
		while (is_meta(str[i++]) == 2)
			flag = 2;
		if (flag == 2)
			count++;
	}
	return (count);
}

int	lex(t_shell *sh, char *str)
{
	sh->commands = malloc(sizeof(char *) * (count_commands(str) + 1));
	if (!sh->commands)
		return (EXIT_FAILURE);
	return (command_loop(sh, str));
}

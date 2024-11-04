/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:09:23 by gnyssens          #+#    #+#             */
/*   Updated: 2024/10/24 17:03:14 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exp_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (s2[i] != '=' && s1[i] != s2[i])
		return (1);
	if (s2[i] == '=' && s1[i] != '\0')
		return (1);
	return (0);
}

int	plus_exp_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s2[i] != '+')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (s2[i] != '+' && s1[i] != s2[i])
		return (1);
	if (s2[i] == '+' && s1[i] != '\0')
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:27:26 by eschmitz          #+#    #+#             */
/*   Updated: 2024/10/22 12:45:07 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_elem(t_shell *sh, int i, int res)
{
	
}

int	check_elem(t_shell *sh, int c, int flag)
{
	int	res;
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (count <= c && sh->command[i] != '\0')
	{
		i += char_index(&sh->command[i]);
		res = i;
		i = check_elem_type(sh, i, res);
		count++;
	}
	if (flag == 1)
		return (res);
	if (flag == 0)
		return (size_elem(sh, i, res));
	return (0);
}

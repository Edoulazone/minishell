/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:39:47 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/12 17:43:04 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_token *lst, t_token *new)
{
	if (!lst || !new)
		return ;
	if ((lst) == NULL)
	{
		lst = new;
		return ;
	}
	ft_lstlast(lst)->next = new;
}

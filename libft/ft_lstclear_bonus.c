/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:20:40 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/12 15:56:58 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_token *lst, void (*del)(void *))
{
	t_token	*ptr1;
	t_token	*ptr2;

	if (!lst || !del || !lst)
		return ;
	ptr1 = lst;
	while (ptr1 != NULL)
	{
		ptr2 = ptr1->next;
		del(ptr1->content);
		free(ptr1);
		ptr1 = ptr2;
	}
	lst = NULL;
}

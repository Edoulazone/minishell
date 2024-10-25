/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:20:40 by gnyssens          #+#    #+#             */
/*   Updated: 2024/04/18 15:48:20 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr1;
	t_list	*ptr2;

	if (!lst || !del || !*lst)
		return ;
	ptr1 = *lst;
	while (ptr1 != NULL)
	{
		ptr2 = ptr1->next;
		del(ptr1->content);
		free(ptr1);
		ptr1 = ptr2;
	}
	*lst = NULL;
}

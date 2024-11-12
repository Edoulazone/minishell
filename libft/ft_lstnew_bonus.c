/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:55:05 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/12 16:10:30 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_token	*ft_lstnew(void *content, int type)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->t_type = type;
	new_node->next = NULL;
	return (new_node);
}

/*
int main(void)
{
	t_list	*node;

	node = ft_lstnew(ft_strdup("Hello"));
	printf("%s", node->content);
	free(node);
	return (0);
}
*/

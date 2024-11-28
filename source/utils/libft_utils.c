/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:50:05 by eschmitz          #+#    #+#             */
/*   Updated: 2024/11/15 18:50:46 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_token	*ft_lstlast(t_token *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}

void	ft_lstadd_back(t_shell *sh, t_token *new)
{
	if (!new)
		return ;
	if ((sh->token) == NULL)
	{
		sh->token = new;
		return ;
	}
	ft_lstlast(sh->token)->next = new;
}

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

size_t	ft_strlen(const char *src)
{
	size_t				i;
	unsigned const char	*new_src;

	if (!src)
		return (0);
	new_src = (unsigned const char *)src;
	i = 0;
	while (new_src[i])
		i++;
	return (i);
}

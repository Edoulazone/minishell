/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:50:05 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/10 18:34:58 by eschmitz         ###   ########.fr       */
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

void	ft_lstadd_back(t_token **token, t_token *new)
{
	if (!new || !token)
		return ;
	if ((*token) == NULL)
	{
		*token = new;
		return ;
	}
	ft_lstlast(*token)->next = new;
}

void	ft_lstclear(t_token **lst, void (*del)(void *))
{
	t_token	*temp;

	if (*lst)
	{
		while ((*lst)->next)
		{
			temp = *lst;
			del((*lst)->content);
			(*lst) = (*lst)->next;
			free(temp);
			temp = NULL;
		}
	}
	return ;
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

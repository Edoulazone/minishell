/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:40:17 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/11 15:34:34 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if (!dst && !src)
		return (NULL);
	if (dst != src)
		while (++i < n)
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
	return (dst);
}

char	*ft_realloc(char *ptr, size_t new_size)
{
	char	*new_ptr;
	size_t	old_size;

	if (ptr == NULL)
		return (malloc(new_size * sizeof(char)));
	if (new_size == 0)
	{
		free(ptr);
		ptr = NULL;
		return (NULL);
	}
	new_ptr = malloc(new_size * sizeof(char));
	if (new_ptr == NULL)
		return (NULL);
	old_size = ft_strlen(ptr);
	if (old_size < new_size)
		ft_memcpy(new_ptr, ptr, old_size);
	else
		ft_memcpy(new_ptr, ptr, new_size);
	free(ptr);
	return (new_ptr);
}

void	check_node_null(t_shell *sh)
{
	t_token	*current;
	t_token	*prev;
	t_token	*temp;

	current = sh->expander;
	prev = NULL;
	while (current)
	{
		if (!current->content)
		{
			temp = current->next;
			if (prev)
				prev->next = temp;
			else
				sh->expander = temp;
			free(current);
			current = temp;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

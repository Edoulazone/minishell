/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:42:53 by gnyssens          #+#    #+#             */
/*   Updated: 2024/05/07 12:23:18 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	my_strlen(char *str)
{
	ssize_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*init_remainder(char *remain, char **buffer)
{
	*buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!(*buffer))
	{
		if (remain)
		{
			free(remain);
			remain = NULL;
		}
		return (NULL);
	}
	if (remain != NULL)
		return (remain);
	remain = (char *)malloc(BUFFER_SIZE + 1);
	if (!remain)
		return (NULL);
	*remain = '\0';
	return (remain);
}

void	my_bzero(char *s, ssize_t n)
{
	ssize_t	i;

	if (!s || 0 == n)
		return ;
	i = 0;
	while (n > 0)
	{
		s[i] = '\0';
		i++;
		n--;
	}
}

char	*myy_strdup(char *str)
{
	ssize_t	len;
	ssize_t	i;
	char	*ptr;

	if (!str)
		return (NULL);
	len = my_strlen(str);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*my_strjoin(char *s1, char *s2)
{
	size_t	len;
	char	*result;
	size_t	i;
	size_t	j;

	len = my_strlen(s1) + my_strlen(s2);
	result = (char *)malloc(len + 1);
	if (!result)
		return (free(s1), NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (free(s1), result);
}

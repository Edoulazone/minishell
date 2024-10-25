/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:35:17 by eschmitz          #+#    #+#             */
/*   Updated: 2024/10/17 19:18:23 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *str)
{
	char	*dup;
	int		len;
	int		i;

	len = 0;
	i = -1;
	while (str[len] != '\0')
		len++;
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	while (++i < len)
		dup[i] = str[i];
	dup[i] = '\0';
	return (dup);
}

char	*ft_strndup(const char *str, int n)
{
	char	*dup;
	int		len;
	int		i;

	len = 0;
	i = -1;
	while (str[len] != '\0')
		len++;
	if (len > n)
		len = n;
	dup = malloc(sizeof(char) * len + 1);
	if (!dup)
		return (NULL);
	while (++i < len)
		dup[i] = str[i];
	dup[i] = '\0';
	return (dup);
}

char	*ft_ssearch(char *str, int c, int flag)
{
	int	i;

	i = -1;
	while (c >= 256)
		c -= 256;
	while (str[++i] != '\0')
	{
		if (str[i] == c && flag == 0)
			return (&str[i + 1]);
		else if (str[i] == c && flag == 1)
			return (ft_strndup(str, i));
	}
	if (c == '\0')
		return (&str[i]);
	return (NULL);
}

void	*ft_bzero(void *str, size_t tot_elem)
{
	while (tot_elem--)
		*(char *)str++ = '\0';
}

void	*ft_calloc(size_t num_elem, size_t size)
{
	void	*mem;

	mem = malloc(num_elem * size);
	if (!mem)
		return (0);
	ft_bzero(mem, num_elem * size);
	return (mem);
}

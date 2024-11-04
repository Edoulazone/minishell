/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:35:17 by eschmitz          #+#    #+#             */
/*   Updated: 2024/11/04 16:55:58 by eschmitz         ###   ########.fr       */
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

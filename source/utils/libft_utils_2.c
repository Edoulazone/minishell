/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:01:00 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/16 17:07:49 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *str)
{
	int		len;
	int		i;
	char	*ptr;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	i = 0;
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*result;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	result = (char *)malloc(len + 1);
	if (!result)
		return (0);
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
	return (result);
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

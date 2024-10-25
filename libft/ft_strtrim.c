/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:48:19 by gnyssens          #+#    #+#             */
/*   Updated: 2024/04/15 20:00:32 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	issep(char const *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	first_trim(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (issep(set, s1[i]) == 1 && s1[i])
		i++;
	return (i);
}

static size_t	end_trim(char const *s1, char const *set)
{
	size_t	len;
	size_t	count;

	len = ft_strlen(s1);
	count = 0;
	while (issep(set, s1[len - 1]) == 1 && len > 0)
	{
		len--;
		count++;
	}
	return (count);
}

static size_t	only_sep(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && issep(set, s1[i]) == 1)
		i++;
	if (s1[i] == '\0')
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	first_num;
	size_t	end_num;
	size_t	len;
	char	*result;

	if (!s1 || !set)
		return (0);
	if (only_sep(s1, set) == 1)
	{
		result = malloc(1);
		if (!result)
			return (0);
		result[0] = '\0';
		return (result);
	}
	first_num = first_trim(s1, set);
	end_num = end_trim(s1, set);
	len = ft_strlen(s1);
	result = (char *)malloc(len - first_num - end_num + 1);
	if (!result)
		return (0);
	ft_memcpy(result, s1 + first_num, len - first_num - end_num);
	result[len - first_num - end_num] = '\0';
	return (result);
}

/*
int main(void)
{
	char const phrase[] = "         ";//" ! phrase ! miteuse : de test!:!";
	char const set[] = ": !";

	char *final = ft_strtrim(phrase, set);
	printf("%s\n", final);
	free(final);

	return (0);
}
*/
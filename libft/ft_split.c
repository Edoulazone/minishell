/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:27:45 by gnyssens          #+#    #+#             */
/*   Updated: 2024/04/18 15:16:41 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static size_t	ft_length_word(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

static char	**free_all(char **dptr, size_t	x)
{
	size_t	i;

	i = 0;
	while (i < x)
	{
		free(dptr[i]);
		i++;
	}
	free(dptr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	t_getal	getal;

	if (!s)
		return (NULL);
	getal.words = ft_count_words(s, c);
	getal.final = (char **)malloc(sizeof(char *) * (getal.words + 1));
	if (!getal.final)
		return (NULL);
	getal.i = 0;
	getal.x = 0;
	while (getal.x < getal.words)
	{
		while (s[getal.i] == c && s[getal.i])
			getal.i++;
		getal.final[getal.x] = malloc(ft_length_word(s + getal.i, c) + 1);
		if (!getal.final[getal.x])
			return (free_all(getal.final, getal.x));
		getal.j = 0;
		while (s[getal.i] != c && s[getal.i])
			getal.final[getal.x][getal.j++] = s[getal.i++];
		getal.final[getal.x][getal.j] = '\0';
		getal.x++;
	}
	getal.final[getal.x] = NULL;
	return (getal.final);
}

/*
int main(void)
{
	char const phrase[] = "phrase miteuse de test";
	char sep = ' ';

	char	**result = ft_split(phrase, sep);

	for (int i = 0; i < 4; i++)
		printf("%s\n", result[i]);

	free(result);

	return 0;
}
*/
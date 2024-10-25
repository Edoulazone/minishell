/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:48:17 by gnyssens          #+#    #+#             */
/*   Updated: 2024/04/17 15:30:40 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t			ind;

	ind = ft_strlen(str);
	if (*(str + ind) == 0 && (char) c == '\0')
		return ((char *) str + ind);
	while (ind >= 1)
	{
		if ((char) str[ind - 1] == (char) c)
			return ((char *)str + ind - 1);
		ind--;
	}
	return (0);
}

/*
int main(void)
{
	const char test[] = "teste"; //"ou est le R ici ?";
	char *reponse = ft_strrchr(test, '\0');

	printf("%s\n", reponse);

	return 0;
}
*/

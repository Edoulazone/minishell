/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:27:05 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/06 13:58:02 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_octets(long n)
{
	int	o;

	if (n == 0)
		return (1);
	if (n < 0)
	{
		o = 1;
		n *= -1;
	}
	else
		o = 0;
	while (n)
	{
		n /= 10;
		o++;
	}
	return (o);
}

char	*ft_itoa(int n)
{
	char		*str;
	long int	nbr;
	int			i;

	nbr = n;
	str = malloc((ft_octets(nbr) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[ft_octets(nbr)] = '\0';
	i = ft_octets(nbr) - 1;
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	if (nbr == 0)
		str[i] = (nbr % 10) + '0';
	while (nbr)
	{
		str[i] = (nbr % 10) + '0';
		nbr /= 10;
		i--;
	}
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	while (src[j])
		j++;
	if (dstsize == 0)
		return (j);
	i = 0;
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return ((size_t)j);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
	{
		while (*s)
		{
			write(fd, s, 1);
			s++;
		}
	}
}

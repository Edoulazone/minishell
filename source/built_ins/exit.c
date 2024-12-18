/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:51:49 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/18 15:40:55 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	my_atoi(const char *str)
{
	int			sign;
	long long	res;
	long long	buff;

	if (!str)
		return (0);
	sign = 1;
	res = 0;
	buff = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= (-1);
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str++ - '0';
		if (buff > res && sign > 0)
			return (-1);
		else if (buff > res && sign < 0)
			return (0);
		buff = res;
	}
	return ((long long) sign * res);
}

void	exit_non_num(t_shell *sh)
{
	ft_free(sh);
	free_env_list(sh->env);
	g_exit_status = 255;
	exit(g_exit_status);
}

void	exit_no_arg(t_shell *sh)
{
	ft_free(sh);
	free_env_list(sh->env);
	exit(g_exit_status);
}

int	non_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+' || str[i] == 32)
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i++] > '9')
		{
			write(2, "minishell: exit: ", 18);
			write(2, str, ft_strlen(str));
			write(2, ": numeric argument required\n", 28);
			return (1);
		}
	}
	if (my_atoi(str) > 2147483647999999999)
	{
		write(2, "minishell: exit: ", 18);
		write(2, str, ft_strlen(str));
		write(2, ": numeric argument required\n", 28);
		return (1);
	}
	return (0);
}

void	ft_exit(t_cmd *node, t_shell *sh)
{
	long long	x;

	decrement_shell_level(sh->env);
	if (!node->arg[1])
		exit_no_arg(sh);
	else if (non_numeric(node->arg[1]))
		exit_non_num(sh);
	else if (node->arg[2] != NULL)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		g_exit_status = 1;
		return ;
	}
	x = my_atoi(node->arg[1]);
	g_exit_status = (int) x % 256;
	ft_free(sh);
	free_env_list(sh->env);
	exit(g_exit_status);
}

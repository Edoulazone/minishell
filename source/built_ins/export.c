/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:59:37 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/18 18:50:43 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_arg(char *var)
{
	int	i;

	if (!((*var >= 'A' && *var <= 'Z') || *var == 95
			|| (*var >= 'a' && *var <= 'z')))
		return (-1);
	i = -1;
	while (var[++i] && var[i] != '=')
	{
		if ((var[i] < '0' && var[i] != '+')
			|| (var[i] > '9' && var[i] < 'A' && var[i] != '=')
			|| (var[i] > 'Z' && var[i] < 'a' && var[i] != '_') || var[i] > 'z')
			return (-1);
	}
	i = -1;
	while (var[++i])
	{
		if (var[i] == '=')
		{
			if (var[i - 1] == '+')
				return (-2);
			else
				return (i);
		}
	}
	return (0);
}

t_env	*env_var_exists(char *var, t_env *env)
{
	while (env)
	{
		if (exp_strcmp(env->value, var) == 0
			|| plus_exp_strcmp(env->value, var) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	append_node(char *var, t_env *env, int sign)
{
	while (env->next != NULL)
		env = env->next;
	env->next = (t_env *)safe_malloc(sizeof(t_env));
	env = env->next;
	if (sign > 0)
	{
		env->value = strdup_until_c(var, '=');
		env->content = safe_strdup(var + sign + 1);
	}
	else if (sign == 0)
	{
		env->value = safe_strdup(var);
		env->content = NULL;
	}
	else if (sign == -2)
	{
		env->value = strdup_until_c(var, '+');
		env->content = safe_strdup(var + length_untill_c(var, '+') + 2);
	}
	env->next = NULL;
}

void	update_content(t_env *node, char *new_var, int sign)
{
	if (node->content && sign != -2)
		free(node->content);
	if (sign > 0)
		node->content = safe_strdup(new_var + sign + 1);
	else if (sign == 0)
		node->content = NULL;
	else if (sign == -2)
	{
		if (node->content == NULL)
			node->content = safe_strdup(new_var
					+ length_untill_c(new_var, '+') + 2);
		else
			node->content = safe_strjoin(node->content, new_var
					+ length_untill_c(new_var, '+') + 2);
	}
}

void	ft_export(t_cmd *node, t_env **env)
{
	char	**args;
	int		i;
	int		spot_equal_sign;

	args = node->arg;
	if (!args[1] || args[1][0] == '\0')
		return (print_export(*env));
	i = 0;
	g_exit_status = 0;
	while (args[++i])
	{
		spot_equal_sign = valid_arg(args[i]);
		if (spot_equal_sign == -1)
		{
			write(2, "minishell: ", 11);
			write(2, node->arg[1], ft_strlen(node->arg[1]));
			my_write(2, ": not a valid identifier\n", 2);
		}
		else if (env_var_exists(args[i], *env) == NULL)
			append_node(args[i], *env, spot_equal_sign);
		else
			update_content(env_var_exists(args[i], *env),
				args[i], spot_equal_sign);
	}
}

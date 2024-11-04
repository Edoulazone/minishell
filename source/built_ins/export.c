/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:59:37 by gnyssens          #+#    #+#             */
/*   Updated: 2024/10/24 16:24:24 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//0 is VALID without content, -1 is NOT VALID, >=1 rank of first '='
//faudra changer, pcq enfaite il peut y avoir un truc sans '=', juste alors ya pas de 'content'
int	valid_arg(char *var)
{
	int	i;

	if (!((*var >= 'A' && *var <= 'Z') || *var == 95 || (*var >= 'a' && *var <= 'z')))
		return (-1); //impossible variable name
	i = -1;
	while (var[++i])
	{
		if ((var[i] < '0' && var[i] != '+')
			|| (var[i] > '9' && var[i] < 'A' && var[i] != '=')
			|| (var[i] > 'Z' && var[i] < 'a' && var[i] != '_') || var[i] > 'z')
			return (-1);
	}
	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
		{
			if (var[i - 1] == '+')
				return (-2); //pr gerer le cas '+='
			else
				return (i);
		}
		i++;
	}
	return (0);
}
//elle renvoie l'addresse du node si VAR existe, et -1 s'il n'existe pas
t_env	*env_var_exists(char *var, t_env *env)
{
	while (env)
	{
		if (exp_strcmp(env->value, var) == 0 || plus_exp_strcmp(env->value, var) == 0)
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
		env->content = safe_strdup(var + sign + 1); //avant sign etait `length_untill_c(var, '=')`
	}
	else if (sign == 0)
	{
		env->value = safe_strdup(var);
		env->content = NULL;
	}
	else if (sign == -2) //cest qd ya +=
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
			node->content = safe_strdup(new_var + length_untill_c(new_var, '+') + 2);
		else
			node->content = safe_strjoin(node->content, new_var + length_untill_c(new_var, '+') + 2);
	}
}

// 1: sans arguments, 2: variable existente (= overwrite),
// 3: nouvelle env variable, 4: invalid argument (genre sans =, ou rien devant/ap res =)
void	ft_export(t_ast *cmd, t_env **env)
{
	char	**args;
	int		i;
	int		spot_equal_sign; //endroit ou ya le '=' dans args[i]

	args = cmd->value;
	if (!(cmd->value)[1])
		return(print_export(*env));
	i = 1;
	while (args[i])
	{
		spot_equal_sign = valid_arg(args[i]);
		if (spot_equal_sign == -1)
		{
			write(1, "argument invalid !!!!\n", 22);
			break;
		}
		else if (env_var_exists(args[i], *env) == NULL)
			append_node(args[i], *env, spot_equal_sign);
		else
			update_content(env_var_exists(args[i], *env), args[i], spot_equal_sign);
		i++;
	}
}

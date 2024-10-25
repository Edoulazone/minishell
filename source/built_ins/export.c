/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:59:37 by gnyssens          #+#    #+#             */
/*   Updated: 2024/10/15 16:21:36 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//1 is VALID, 0 is NOT valid
int	valid_arg(char *var)
{
	int	i;

	i = 0;
	while (var[i] == ' ')
		i++;
	if (var[i] == '=')
		return (0);
	while (var[i] && var[i] != '=')
		i++;
	i += 1;
	if (!var[i])
		return (0);
	while (var[i] == ' ')
		i++;
	if (!var[i])
		return (0);
	while (var[i])
	{
		if (var[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

//faudrait qu'elle renvoie la position du node si VAR existe, et -1 s'il n'existe pas
t_list	*env_var_exists(char *var, t_list *env)
{
	while (env)
	{
		if (exp_strcmp(var, env->content) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	append_node(char *var, t_list *env)
{
	while (env->next != NULL)
		env = env->next;
	env->next = (t_list *)malloc(sizeof(t_list));
	if (!env->next)
	{
		write(1, "malloc failed !\n", 16);
		//free lists etc.
		exit(EXIT_FAILURE);
	}
	env = env->next;
	env->content = ft_strdup(var); //faudra faire un safe_strdup
	env->next = NULL;
}

void	update_content(t_list *node, char *new_var)
{	
	free(node->content);
	node->content = ft_strdup(new_var); //pas protégé, safe_strdup
}

// 1: sans arguments, 2: variable existente (= overwrite),
// 3: nouvelle env variable, 4: invalid argument (genre sans =, ou rien devant/apres =) 
void	ft_export(t_ast_command *cmd, t_list **env)
{
	char	**args;
	int		i;

	args = cmd->args;
	if (!(cmd->args)[1])
		return(ft_env(*env));
	i = 1;
	while (args[i])
	{
		if (!valid_arg(args[i]))
		{
			write(1, "argument invalid !\n", 19);
			break;
		}
		else if (env_var_exists(args[i], *env) == NULL)
			append_node(args[i], *env);
		else
			update_content(env_var_exists(args[i], *env), args[i]);
		i++;
	}
}

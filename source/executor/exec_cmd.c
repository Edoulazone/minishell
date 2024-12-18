/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:45:40 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/18 14:49:08 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	decrement_shell_level(t_env *env)
{
	int		temp;
	t_env	*node;
	char	*new_str;

	node = get_node(env, "SHLVL");
	if (!node)
		return ;
	temp = my_atoi(node->content) - 1;
	new_str = malloc(sizeof(char) * 16);
	if (!new_str)
		return ;
	if (temp < 1 || temp > 1000)
		temp = 1;
	new_str = ft_itoa(temp);
	node->content = new_str;
}

void	increment_shell_level(t_env *env)
{
	int		temp;
	t_env	*node;
	char	*new_str;

	node = get_node(env, "SHLVL");
	if (!node)
		return ;
	temp = my_atoi(node->content) + 1;
	new_str = malloc(sizeof(char) * 16);
	if (!new_str)
		return ;
	if (temp < 1 || temp > 1000)
		temp = 1;
	new_str = ft_itoa(temp);
	node->content = new_str;
}

void	add_path(t_cmd *node, t_env *env)
{
	int		i;
	char	**split_path;
	char	*check;
	char	*temp;

	while (env && ft_strcmp(env->value, "PATH"))
		env = env->next;
	if (!env || ft_strcmp(env->value, "PATH"))
		return ;
	split_path = ft_split(env->content, ':');
	i = -1;
	while (split_path[++i])
	{
		check = safe_strjoin(split_path[i], "/");
		temp = check;
		check = safe_strjoin(check, node->arg[0]);
		free(temp);
		if (access(check, X_OK) == 0)
		{
			free(node->arg[0]);
			node->arg[0] = safe_strdup(check);
			return (free(check), free_split(split_path));
		}
		free(check);
	}
}

int	execute_command(t_cmd *node, t_env *env)
{
	char	**env_array;

	add_path(node, env);
	if (!ft_strcmp(node->arg[0], "./minishell"))
		increment_shell_level(env);
	env_array = env_to_array(env, 0);
	if (!get_node(env, "PATH"))
	{
		free_split(env_array);
		write(2, "minishell: ", 1);
		write(2, node->arg[0], ft_strlen(node->arg[0]));
		write(2, ": No such file or directory\n", 28);
		exit(127);
	}
	g_exit_status = 0;
	if (-1 == execve(node->arg[0], node->arg, env_array))
	{
		free_split(env_array);
		write(2, "minishell: ", 11);
		write(2, node->arg[0], ft_strlen(node->arg[0]));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	exit (g_exit_status);
}

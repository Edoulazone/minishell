/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:45:40 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/06 17:15:29 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    print_full_command(t_cmd *node)
{
    int     i;
	int		j;
    char	**args;	

	args = node->arg;
    i = 0;
    while (args[i])
	{
		j = 0;
		write(1, "\"", 1);
		while (args[i][j])
		{
			write(1, args[i] + j, 1);
			j++;
		}
		write(1, "\", ", 3);
		i++;
	}
	write(1, "\n", 1);
}

void    add_path(t_cmd *node, t_env *env)
{
    int     i;
    char    **split_path;
    char    *check;
    char    *temp; //sert juste a pas avoir de memory leaks avec 'check'

    while (ft_strcmp(env->value, "PATH") != 0)
        env = env->next;
    split_path = ft_split(env->content, ':');
    i = 0;
    while (split_path[i])
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
        i++;
    }
}

//je suppose return int pour errno valeur retour jsp quoi
int execute_command(t_cmd *node, t_env *env, t_shell *sh)
{
    char    **env_array;

    add_path(node, env);
    (void)sh;
    env_array = env_to_array(env);
    fill_env_array(env_array, env);
	if (-1 == execve(node->arg[0], node->arg, env_array))
	{
		free_split(env_array);
		perror("execve failed !\n");
		exit(EXIT_FAILURE);
	}
    return (EXIT_FAILURE);
}


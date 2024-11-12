/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:45:40 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/05 16:40:08 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    add_path(t_ast *cmd, t_env *env)
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
        check = safe_strjoin(check, cmd->value[0]);
        free(temp);
        if (access(check, X_OK) == 0)
        {
            free(cmd->value[0]);
            cmd->value[0] = safe_strdup(check);
            return (free(check), free_split(split_path));
        }
        free(check);
        i++;
    }
}

//je suppose return int pour errno valeur retour jsp quoi
int execute_command(t_ast *cmd, t_env *env, t_shell *sh)
{
    char    **env_array;

    add_path(cmd, env);
    (void)sh;
    env_array = env_to_array(env);
    fill_env_array(env_array, env);
	if (-1 == execve(cmd->value[0], cmd->value, env_array))
	{
		free_split(env_array);
		perror("execve failed !\n"); //surement pas que ca à faire
		exit(EXIT_FAILURE);
	} //return status/value ???
    return (EXIT_FAILURE);
}

void    handle_cmd(t_ast *node, t_env **env, t_shell *sh)
{
    pid_t   pid;

    pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE); // == problem with fork() !
    else if (0 == pid)
        execute_command(node, *env, sh);
    else
        waitpid(pid, &sh->return_value, 0); //wait for child to finish
}

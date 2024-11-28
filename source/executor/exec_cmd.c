/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:45:40 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/20 22:40:38 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    print_full_command(t_ast *node)
{
    int     i;
	int		j;
    char	**arg;	

	arg = node->value;
    i = 0;
    while (arg[i])
	{
		j = 0;
		write(1, "\"", 1);
		while (arg[i][j])
		{
			write(1, arg[i] + j, 1);
			j++;
		}
		write(1, "\", ", 3);
		i++;
	}
	write(1, "\n", 1);
}

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
	// print debugging
	//write(2, "node->value, so full command to be execve: ", 43);
	//print_full_command(cmd);
	//print_value(cmd->value);
    env_array = env_to_array(env);
    fill_env_array(env_array, env);
	//write(2, "\n2e CHECK de l'exec\n", 20);
	if (-1 == execve(cmd->value[0], cmd->value, env_array))
	{
		free_split(env_array);
		perror("execve failed !\n"); //surement pas que ca à faire
		exit(EXIT_FAILURE);
	} //return status/value ???
	exit(EXIT_SUCCESS); //p e du yaourt cette ligne
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

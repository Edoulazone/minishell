/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:28:03 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/18 14:52:41 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_array(char **array)
{
	int		i;
	char	*temp;

	i = 0;
	while (array[i + 1] != NULL)
	{
		if (ft_strcmp(array[i], array[i + 1]) > 0)
		{
			temp = array[i + 1];
			array[i + 1] = array[i];
			array[i] = temp;
			i = 0;
		}
		else
			i++;
	}
}

void	fill_env_array(char **array, t_env *env)
{
	int		i;

	i = 0;
	while (env)
	{
		if (env->content)
			filler(array, env, &i);
		else
			array[i] = safe_strdup(env->value);
		i++;
		env = env->next;
	}
	array[i] = NULL;
}

char	**env_to_array(t_env *env, int mustsort)
{
	int		size;
	t_env	*current;
	char	**env_array;

	size = 0;
	current = env;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	env_array = (char **)safe_malloc(sizeof(char *) * (size + 1));
	fill_env_array(env_array, env);
	if (mustsort)
		sort_array(env_array);
	return (env_array);
}

void	print_helper(char **array, char *temp, int i)
{
	temp = strdup_until_c(array[i], '=');
	write(1, temp, ft_strlen(temp));
	free(temp);
	write(1, "=\"", 2);
	temp = safe_strdup(array[i] + length_untill_c(array[i], '=') + 1);
	write(1, temp, ft_strlen(temp));
	free(temp);
	write(1, "\"", 1);
}

void	print_export(t_env *env)
{
	char	**array;
	int		i;
	char	*temp;

	array = env_to_array(env, 1);
	i = -1;
	temp = NULL;
	while (array[++i])
	{
		write(1, "declare -x ", 11);
		if (is_there_equal(array[i]) == 0)
			write(1, array[i], ft_strlen(array[i]));
		else
			print_helper(array, temp, i);
		write(1, "\n", 1);
	}
	g_exit_status = 0;
	free_split(array);
}

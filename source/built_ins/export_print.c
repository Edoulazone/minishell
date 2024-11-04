/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:28:03 by gnyssens          #+#    #+#             */
/*   Updated: 2024/10/24 15:53:53 by gnyssens         ###   ########.fr       */
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
	char	*temp;
	char double_quote[2];

	double_quote[0] = 34; //34 == "
	double_quote[1] = '\0';
	i = 0;
	while (env)
	{
		if (env->content)
		{
			temp = safe_strjoin(env->value, "=");
			temp = safe_strjoin(temp, double_quote);
			temp = safe_strjoin(temp, env->content);
			temp = safe_strjoin(temp, double_quote);
			array[i] = safe_strdup(temp);
			free(temp);
		}
		else
			array[i] = safe_strdup(env->value);
		i++;
		env = env->next;
	}
	array[i] = NULL;
}

char    **env_to_array(t_env *env)
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
	sort_array(env_array);
	return (env_array);
}

//il manque les "", comme dans declare -x VAR="content", faudrait rajouter idealement
void	print_export(t_env *env)
{
	char	**array;
	int		i;

	array = env_to_array(env);
	i = 0;
	while (array[i])
	{
		write(1, "declare -x ", 11);
		write(1, array[i], ft_strlen(array[i]));
		write(1, "\n", 1);
		i++;
	}
	free_split(array);
}

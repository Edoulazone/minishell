/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimmer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:29:33 by eschmitz          #+#    #+#             */
/*   Updated: 2024/11/28 11:54:03 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_quotes(t_token *token, char *str)
{
	char	*new_str;
	size_t	i;

	new_str = malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (!new_str)
		return ;
	i = 0;
	while (++i < (ft_strlen(str) - 1))
		new_str[i - 1] = str[i];
	new_str[ft_strlen(str) - 2] = '\0';
	token->content = new_str;
}

void	get_env_var(t_shell *sh, t_token *token)
{
	t_env 	*env_copy;
	char	*new_str;
	int		i;

	i = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(token->content) - 1));
	if (!new_str)
		return ;
	while (token->content[++i])
		new_str[i - 1] = token->content[i];
	env_copy = sh->env;
	while (env_copy)
	{
		if (!ft_strcmp(new_str, env_copy->value))
		{
			token->content = NULL;
			token->content = env_copy->content;
			free(new_str);
			return ;
		}
		env_copy = env_copy->next;
	}
	free(new_str);
	return ;
}

void	t_trimmer(t_token *tokens, t_shell *sh)
{
	int		i;
	char	*str;

	if (!tokens || !tokens->content)
		return ;
	while (tokens)
	{
		i = -1;
		str = tokens->content;
		if ((str[0] == '\"' && str[ft_strlen(str) - 1] == '\"') ||
			(str[0] == '\'' && str[ft_strlen(str) - 1] == '\''))
			del_quotes(tokens, str);
		str = tokens->content;
		if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
			while (str && str[++i])
				if (str[i] == '$' && str[i + 1])
					get_env_var(sh, tokens);
		tokens = tokens->next;
	}
}

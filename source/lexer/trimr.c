/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:29:33 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/09 15:23:31 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	if (c == '\"' || c == '\'')
		return (1);
	return (0);
}

// void	get_env_var(t_shell *sh, t_token *token, int indent)
// {
// 	t_env 	*env_copy;
// 	char	*new_str;
// 	int		i;
// 	int		start;

// 	new_str = malloc(sizeof(char) * (ft_strlen(token->content) - 1));
// 	if (!new_str)
// 		return ;
// 	i = 0;
// 	while (is_quote(token->content[indent]))
// 		indent++;
// 	start = indent;
// 	while (token->content[indent] && !is_quote(token->content[indent]))
// 		new_str[i++] = token->content[indent];
// 	env_copy = sh->env;
// 	while (env_copy)
// 	{
// 		if (!ft_strcmp(new_str, env_copy->value))
// 		{
// 			token->content = env_copy->content;
// 			free(new_str);
// 			return ;
// 		}
// 		env_copy = env_copy->next;
// 	}
// 	free(new_str);
// 	return ;
// }

// void	del_quotes(t_token **token, char *str)
// {
// 	char	*new_str;
// 	size_t	i;

// 	new_str = malloc(sizeof(char) * (ft_strlen(str) - 1));
// 	if (!new_str)
// 		return ;
// 	i = 0;
// 	while (++i < (ft_strlen(str) - 1))
// 		new_str[i - 1] = str[i];
// 	new_str[ft_strlen(str) - 2] = '\0';
// 	(*token)->content = new_str;
// }

// void	del_quotes_env(t_token **token, char *str, t_shell *sh)
// {
// 	char	*new_str;
// 	size_t	i;

// 	new_str = malloc(sizeof(char) * (ft_strlen(str) - 1));
// 	if (!new_str)
// 		return ;
// 	i = 0;
// 	while (++i < (ft_strlen(str) - 1))
// 		new_str[i - 1] = str[i];
// 	new_str[ft_strlen(str) - 2] = '\0';
// 	(*token)->content = new_str;
// 	i = 0;
// 	while (new_str && new_str[i])
// 	{
// 		if (new_str[i] == '$' && new_str[i + 1])
// 			get_env_var(sh, *token, i);
// 	}
// }

void	apply_var_to_token(t_shell *sh, int	start, char *env_var, t_token *token)
{
	
}

void	get_env_var(t_shell *sh, t_token *token, int indent)
{
	t_env 	*env_copy;
	char	*new_str;
	int		i;
	int		start;
	
	i = 0;
	new_str = malloc(sizeof(char) * 40);
	if (!new_str)
		return ;
	start = indent;
	while (!is_quote(token->content[indent]))
		new_str[i++] = token->content[indent++];
	env_copy = sh->env;
	while (env_copy)
	{
		if (!ft_strcmp(new_str, env_copy->value))
		{
			apply_var_to_token(sh, start, env_copy->content, token);
			free(new_str);
			return ;
		}
		env_copy = env_copy->next;
	}
	free(new_str);
	return ;
}

void	expander(t_token **token, t_shell *sh, int sqs)
{
	char	*str;
	int		i;

	i = -1;
	str = (*token)->content;
	while (str && str[++i] && !(sqs % 2))
	{
		if (str[i] == '$' && str[i + 1])
			get_env_var(sh, token, i);
	}
}

int	trimmer(char *str, int *sqs, int *dqs, int *c)
{
    int		i;
    int		j;
    char    *result;
    
    i = 0;
    j = 0;
    result = malloc((ft_strlen(str) + 1) * sizeof(char));
    if (!result)
        return (NULL);
    while (str[i])
    {
        if (str[i] == '\'' && *dqs == 0)
			*sqs++;
        else if (str[i] == '\"' && *sqs == 0)
			*dqs++;
        else 
            result[j++] = str[i];
        if (str[i] == '\'')
            *c += 1;
        i++;
    }
    result[j] = '\0';
    return (result);
}

void	expand(char *str, char *new_str, t_shell *sh, int *sqs, int *dqs, int *c)
{
	char	*exit_code_str;
	char	*expanded;
	int		i;
	int		j;
	int		end_index;
	while (str[i])
		{
			if (str[i] == '$' && str[i + 1] && (!(sqs % 2) || !c))
			{
				if (str[i + 1] == '?')
				{
					exit_code_str = ft_itoa(sh->exit_status);
					strncpy(&new_str[j], exit_code_str, ft_strlen(exit_code_str));
					j += ft_strlen(exit_code_str);
					free(exit_code_str);
					i++;
				}
				else
				{
					expanded = get_env_var(&str[i], sh->env, &end_index);
					strncpy(&new_str[i], expanded, ft_strlen(expanded));
					j += ft_strlen(expanded);
					free(expanded);
					i += end_index - 1;
				}
			}
			else
				new_str[j++] = str[i];
			i++;
		}
}

void	trim_and_expand(t_token *tokens, t_shell *sh)
{
	char	*str;
	char	*new_str;
	int		sqs;
	int		dqs;
	int		c;

	sqs = 0;
	dqs = 0;
	c = 0;
	while (tokens)
	{
		str = (char *)tokens->content;
		str = trimmer(str, &sqs, &dqs, &c);
		new_str = malloc(sizeof(char) * 1024);
		if (!new_str)
			return ;
		expand(str, new_str, sh, &sqs, &dqs, &c);
		new_str[ft_strlen(new_str)] = '\0';
		free(tokens->content);
		tokens->content = new_str;
		tokens = tokens->next;
	}
}

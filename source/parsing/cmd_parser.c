/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:48:04 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/11 16:12:02 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_arg(t_token *token)
{
	char	**arg;
	int		i;

	arg = malloc(sizeof(char *) * (ft_lstsize(token) + 1));
	i = 0;
	while (token)
	{
		arg[i] = ft_strdup(token->content);
		token = token->next;
		i++;
	}
	arg[i] = NULL;
	return (arg);
}

t_ast	*cmd_node(char **arg, t_env *env)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->type = CMD;
	cmd->arg = arg;
	cmd->env = env;
	return ((t_ast *)cmd);
}

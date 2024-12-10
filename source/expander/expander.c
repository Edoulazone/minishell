/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:44:42 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/10 19:04:18 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 
 void	heredoc_token(t_shell *sh, t_token *token, char *str)
 {
	ft_lstadd_back(&sh->expander, ft_lstnew(str, token->t_type));
	token = token->next;
	str = expand_heredoc(token->content);
	ft_lstadd_back(&sh->expander, ft_lstnew(str, token->t_type));
 }
 
static void	normal_token(t_shell *sh, t_token *token)
{
	ft_lstadd_back(&sh->expander, ft_lstnew(token->content, token->t_type));
}

static void	word(t_shell *sh, t_token *token, char *str, t_token **expander)
{
	char	*copy;

	copy = get_word(sh, str);
	if (!copy)
		return ;
	printf("token value after expand: %s\n", copy);
	ft_lstadd_back((expander), ft_lstnew(copy, token->t_type));
	// list_append(sh->expander, copy, token->t_type);
	if (*expander && (*expander)->content)
		printf("token value after adding to list: %s\n", (*expander)->content);
	free(copy);
	return ;
}

static void	dispatcher(t_shell *sh, t_token **expander)
{
	char	*str;
	t_token	*token;

	token = sh->token;
	while (token)
	{
		str = token->content;
		if (token->t_type == WORD)
			word(sh, token, str, expander);
		else if (token->t_type == HEREDOC)
		{
			heredoc_token(sh, token, str);
			token = token->next;
		}
		else
			normal_token(sh, token);
		token = token->next;
	}
}

int	expander(t_shell *sh, t_token **expander)
{
	// sh->expander = init_token();
	// if (!sh->expander)
	// {
	// 	printf("Zut\n");
	// 	return (EXIT_FAILURE);
	// }
	sh->env_exp = init_var_exp();
	if (!sh->env_exp)
		return (EXIT_FAILURE);
	dispatcher(sh, expander);
	check_node_null(sh);
	free(sh->env_exp);
	sh->env_exp = NULL;
	return (EXIT_SUCCESS);
}

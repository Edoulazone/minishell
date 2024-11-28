/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:53:52 by eschmitz          #+#    #+#             */
/*   Updated: 2024/11/28 14:05:35 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_meta_token(char *c, int *i)
{
	char	*data;

	if (*c == *(c + 1))
	{
		data = malloc(sizeof(char) * 3);
		data[0] = *c;
		data[1] = *(c + 1);
		data[2] = '\0';
		*i += 1;
		return (data);
	}
	data = malloc(sizeof(char) * 2);
	data[0] = *c;
	data[1] = '\0';
	return (data);
}

char	*get_token(char *str, int *i, int *sqs, int *dqs)
{
	int		j;
	char	*data;

	j = 0;
	*sqs = 0;
	*dqs = 0;
	while (new_qs(str[j], sqs, dqs), str[j] && !is_meta(str[j], sqs, dqs))
		j++;
	data = malloc(sizeof(char) * (j + 1));
	j = 0;
	*sqs = 0;
	*dqs = 0;
	while (new_qs(str[j], sqs, dqs), str[j] && !is_meta(str[j], sqs, dqs))
	{
		data[j] = str[j];
		j++;
	}
	data[j] = '\0';
	*i += j - 1;
	return (data);
}

void	t_type(t_token *token)
{
	while (token)
	{
		// printf("token content: %s\n", token->content);
		if (!ft_strcmp(token->content, "|"))
			token->t_type = PIPE;
		else if (!ft_strcmp(token->content, "<"))
			token->t_type = INPUT;
		else if (!ft_strcmp(token->content, ">"))
			token->t_type = TRUNC;
		else if (!ft_strcmp(token->content, ">>"))
			token->t_type = APPEND;
		else if (!ft_strcmp(token->content, "<<"))
			token->t_type = HEREDOC;
		else
			token->t_type = CMD;
		token = token->next;
	}	
}

int	lex(char *str, t_shell *sh)
{
	int	i;
	int	single_quote_s;
	int	double_quote_s;

	i = 0;
	single_quote_s = 0;
	double_quote_s = 0;
	while (str && str[i])
	{
		if (!is_meta(str[i], &single_quote_s, &double_quote_s))
			ft_lstadd_back(sh, ft_lstnew(get_token(&str[i], &i,
				&single_quote_s, &double_quote_s), CMD));
		else if (is_meta(str[i], &single_quote_s, &double_quote_s) == 1)
			ft_lstadd_back(sh, ft_lstnew(get_meta_token(&str[i], &i), CMD));
		i++;
	}
	check_qs(single_quote_s, double_quote_s, sh->token);
	t_type(sh->token);
	if (verif_lex(sh, sh->token))
		return (1);
	t_trimmer(sh->token, sh);
	return (0);
}

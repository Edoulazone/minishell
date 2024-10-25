/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:05:41 by eschmitz          #+#    #+#             */
/*   Updated: 2024/10/17 15:09:56 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	is_space(int c)
// {
// 	if (c == ' ' || c == '\t' || c == '\n'
// 		|| c == '\r' || c == '\f')
// 		return (1);
// 	return (0);
// }

// int	is_token(int c)
// {
// 	if (c == '(' || c == ')' || c == '<' || c == '>' || c == '&' || c == '|')
// 		return (1);
// 	return (0);
// }

// int	lexer(char *input, t_shell *sh)
// {
// 	t_token			*token;
// 	size_t			i;
// 	size_t			len;

// 	i = 0;
// 	*token_list = NULL;
// 	while (input[i])
// 	{
// 		len = 0;
// 		if (!is_space(input[i]))
// 		{
// 			type = scan_next_token(input + 1, &len, sh);
// 			if (type == TK_ERROR)
// 				return (report_suntax_error(sh));
// 			token = create_token(type, input + i, len, sh);
// 			list_add_back_shell(token, token_list, PROMPT, sh);
// 		}
// 		else
// 			len++;
// 		i += len;
// 	}
// 	return (EXIT_SUCCESS);
// }

// t_token	*create_token(char *value, t_shell *sh)
// {
// 	t_token	*token;
// 	t_token	*current;

// 	token = calloc_s(1, sizeof(t_token), PROMPT, sh);
// 	token->type = type;
// 	token->value = s_alloc(ft_substr(value, 0, len), PROMPT, sh);
// 	return (token);
// }

int	lexer(t_shell *sh)
{
	int	i;

	i = 0;
	split_command(sh->command);
	
}
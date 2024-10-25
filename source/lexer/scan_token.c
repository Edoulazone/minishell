/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:30:59 by eschmitz          #+#    #+#             */
/*   Updated: 2024/10/02 14:24:07 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	scan_token_logic_and_pipe(char *input, char c,
	size_t *len, t_shell *sh)
{
	while (input[*len] == c)
		(*len)++;
	if (c == '&')
	{
		if (*len == 2)
			return (TK_AND);
		else if (*len == 1 || *len == 3)
			set_syntax_error("&", sh);
		else
			set_syntax_error("&&", sh);
	}
	else if (c == '|')
	{
		if (*len == 1)
			return (TK_PIPE);
		else if (*len == 2)
			return (TK_OR);
		else
			set_syntax_error("||", sh);
	}
	return (TK_ERROR);
}

t_token_type	scan_token_subshell(char *input, size_t *len)
{
	(*len)++;
	if (*input == '(')
		return (TK_SUBSHELL_OPEN);
	return (TK_SUBSHELL_CLOSE);
}

t_token_type	scan_tk_redirect(char *input, char c, size_t *len, t_shell *sh)
{
	while (input[*len] == c)
		*len += 1;
	if (c == '<' && *len == 1)
		return (TK_REDIRECT_IN);
	else if (c == '<' && *len == 2)
		return (TK_HEREDOC);
	else if (c == '>' && *len == 1)
		return (TK_REDIRECT_OUT);
	else if (c == '>' && *len == 2)
		return (TK_APPEND_OUT);
	set_syntax_error(input, sh);
	return (TK_ERROR);
}

t_token_type	scan_token_word(char *input, size_t *len, t_shell *sh)
{
	char	c;
	bool	in;

	in = false;
	while (input[*len])
	{
		if (input[*len + 1] && input[*len] == '\\')
			(*len)++;
		else if (input[*len] == '\"' || input[*len] == '\'')
		{
			if (!in)
			{
				c = input[*len];
				in = true;
			}
			else if ((is_token(input[*len]) || is_space(input[*len])) && !in)
				break ;
			(*len)++;
		}
		if (in)
			return (set_syntax_error("unclosed quote", sh), TK_ERROR);
		return (TK_WORD);
	}
}

t_token_type	scan_next_token(char *input, size_t *len, t_shell *sh)
{
	if (*input == '&' || *input == '|')
		return (scan_token_logic_and_pipe(input, *input, len, sh));
	else if (*input == '<' || *input == '>')
		return (scan_tk_redirect(input, *input, len, sh));
	else if (*input == '(' || *input == ')')
		return (scan_token_subshell(input, len));
	return (scan_token_word(input, len, sh));
}

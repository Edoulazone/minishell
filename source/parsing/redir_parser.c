/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:48:07 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/17 17:42:13 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc(char *delimiter, char *file)
{
	char	*buff;
	int		fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	signal(SIGINT, exit);
	while (1)
	{
		handle_signal(0);
		buff = readline("> ");
		if (buff == NULL)
			return ;
		if (!ft_strcmp(delimiter, buff))
			break ;
		ft_putstr_fd(buff, fd);
		ft_putstr_fd("\n", fd);
		free(buff);
	}
	if (buff)
		free (buff);
	close(fd);
}

t_ast	*redir_node(char *file, t_ast *cmd, int type)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	redir->type = type;
	if (cmd)
		redir->cmd = cmd;
	else
		redir->cmd = NULL;
	redir->file = file;
	return ((t_ast *)redir);
}

int	ft_check_other_redir(t_token *token)
{
	t_token	*tokens;

	tokens = token->next;
	while (tokens)
	{
		if (!token_is_redir(tokens))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

t_token	*get_previous_redir(t_token *token)
{
	t_token	*prev;

	prev = NULL;
	while (token_is_redir(token))
	{
		ft_lstadd_back(&prev, ft_lstnew(ft_strdup(token->content),
				token->t_type));
		token = token->next;
	}
	token = token->next;
	if (token && token-> t_type == WORD)
	{
		token = token->next;
	}
	while (token)
	{
		ft_lstadd_back(&prev, ft_lstnew(ft_strdup(token->content),
				token->t_type));
		token = token->next;
	}
	return (prev);
}

char	*get_file_type(t_token *token, int *type, int *hd_index)
{
	t_token	*start_lst;
	char	*hd_file;
	char	*index;

	start_lst = token;
	while (token_is_redir(token))
		token = token->next;
	*type = token->t_type;
	token = token->next;
	if (token)
	{
		if (*type == HEREDOC)
		{
			index = ft_itoa(*hd_index);
			hd_file = ft_strjoin("/tmp/hd_file", index);
			free(index);
			(*hd_index)--;
			ft_heredoc(token->content, hd_file);
			return (hd_file);
		}
		else
			return (ft_strdup(token->content));
	}
	else
		return (ft_strdup("\n"));
}

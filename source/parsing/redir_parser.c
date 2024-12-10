/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:48:07 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/06 16:31:32 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp2(char *str, char *str_to_find)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while ((str[i] && str[i] != '\n') || str_to_find[i])
	{
		if (str[i] != str_to_find[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_cmdlen(char *str)
{
	int	i;

	i = 0;
	str = str + 2;
	while (str[i] != ')')
		i++;
	return (i);
}

t_token	*ft_delheredoc(t_token **token)
{
	t_token	*current;
	t_token	*new_lst;

	current = *token;
	new_lst = NULL;
	while (current)
	{
		if (current->t_type == HEREDOC)
		{
			current = current->next->next;
		}
		else
		{
			ft_lstadd_back(&new_lst, ft_lstnew(ft_strdup(current->content),
					current->t_type));
			current = current->next;
		}
	}
	ft_lstclear(token, &free);
	return (new_lst);
}

void	ft_del_hdfiles(void)
{
	char	*file;
	char	*index;
	int		flag;

	flag = 1;
	while (flag)
	{
		index = ft_itoa(flag);
		file = ft_strjoin("/tmp/hd_file", index);
		if (!access(file, F_OK))
		{
			unlink(file);
		}
		else
			flag = -1;
		flag++;
		free(file);
		free(index);
	}
}

void	ft_write_hdline(char *str, char *file)
{
	int		fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		error("open");
	while (*str)
	{
		if (*str == '$' && *(str + 1) == '(' && ft_strchr(str, ')'))
		{
			str += ft_cmdlen(str) + 3;
		}
		else
		{
			write(fd, str, 1);
			if (*(str + 1) == '\0')
				write(fd, "\n", 1);
			str++;
		}
	}
	close(fd);
}

void	ft_heredoc(char *delimiter, char *file)
{
	char	*buff;
	int		fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// gab signals function;
	while (1)
	{
		buff = readline("> ");
		if (buff == NULL)
			exit (0);
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

t_ast	*redir_node(char *file, t_ast *cmd, int type, t_token **token)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	redir->type = type;
	redir->cmd = cmd;
	redir->file = file;
	ft_lstclear(token, &free);
	return ((t_ast *)redir);
}

int	token_is_redir(t_token *token)
{
	if (!token)
		return (1);
	if (token->t_type == INPUT || token->t_type == HEREDOC)
		return (0);
	if (token->t_type == APPEND || token->t_type == TRUNC)
		return (0);
	return (1);
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
		token = token->next;
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
	(void) start_lst; // MODIF TO COMPILE 
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

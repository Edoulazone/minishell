/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:17:55 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/11 16:12:35 by eschmitz         ###   ########.fr       */
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

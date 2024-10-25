/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:15:52 by gnyssens          #+#    #+#             */
/*   Updated: 2024/08/06 16:52:02 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	end_of_line(char *line)
{
	ssize_t	i;

	i = 0;
	while (line[i])
	{
		if ('\n' == line[i])
			return (i);
		i++;
	}
	i = 0;
	return (-1);
}

char	*dupl_and_adjust_remain(char *remain)
{
	ssize_t	i;
	ssize_t	j;
	char	*new_line;

	new_line = myy_strdup(remain);
	if (!new_line)
		return (NULL);
	i = 0;
	while (new_line[i] && new_line[i] != '\n')
		i++;
	if ('\n' == new_line[i])
	{
		j = i + 1;
		while (new_line[++i] != '\0')
			new_line[i] = '\0';
		i = 0;
		while (remain[j])
			remain[i++] = remain[j++];
		remain[i] = '\0';
	}
	else if ('\0' == new_line[i])
		my_bzero(remain, i + 1);
	return (new_line);
}

char	extract_buffer(int fd, char *buffer)
{
	ssize_t	count;
	ssize_t	i;

	count = read(fd, buffer, BUFFER_SIZE);
	if (count < 0)
		return ('e');
	buffer[count] = '\0';
	if (count == 0)
		return ('\0');
	i = 0;
	while (i < count)
	{
		if ('\n' == buffer[i])
			return ('\n');
		i++;
	}
	return ('c');
}

ssize_t	manage_extraction(int fd, char *buf, char **line)
{
	char	check;
	ssize_t	i;

	check = 'c';
	while (check == 'c')
	{
		check = extract_buffer(fd, buf);
		if (check == 'c')
			*line = my_strjoin(*line, buf);
		if (!(*line))
			return (-1);
	}
	if (check == '\n')
	{
		*line = my_strjoin(*line, buf);
		if (!(*line))
			return (-1);
		i = end_of_line(*line) + 1;
		while ((*line)[i] != 0)
			(*line)[i++] = '\0';
		return (0);
	}
	if (check == 'e')
		return (free(*line), -1);
	return (2);
}

char	*get_next_line(int fd)
{
	t_variable	v;
	static char	*rest = NULL;

	v.buffer = NULL;
	rest = init_remainder(rest, &v.buffer);
	if (!rest || fd < 0)
		return (free(v.buffer), NULL);
	v.line = dupl_and_adjust_remain(rest);
	if (!v.line)
		return (free(rest), rest = NULL, free(v.buffer), NULL);
	if (end_of_line(v.line) >= 0)
		return (free(v.buffer), v.buffer = NULL, v.line);
	v.check = manage_extraction(fd, v.buffer, &(v.line));
	if (v.check == -1)
		return (free(rest), rest = NULL, free(v.buffer), NULL);
	else if (v.check == 0)
	{
		v.i = end_of_line(v.buffer);
		while (v.buffer[++(v.i)] != '\0')
			rest[v.check++] = v.buffer[v.i];
		rest[v.check] = '\0';
	}
	if (*(v.line) == '\0')
		return (free(rest), rest = NULL, free(v.line), free(v.buffer), NULL);
	return (free(v.buffer), v.line);
}

/*
int main() {
    int fd;
    char *line;

    fd = open("tekst.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return (1);
    }
	
	int i = 0;
	while (i < 12) // && line != NULL)
	{
		line = get_next_line(fd);
        printf("%d'th line: %s", i + 1, line); 
		if(line == NULL)
			exit(0); // Print each line as it's read
		free(line); // Don't forget to free memory!
		i++;
    }

    close(fd);
    return (0);
}
*/

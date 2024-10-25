/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:42:58 by gnyssens          #+#    #+#             */
/*   Updated: 2024/05/07 12:42:43 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# if BUFFER_SIZE >= 2147483647
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 2147483646
# endif

// LIBRAIRIES
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

// STRUCTURE
typedef struct s_variable
{
	ssize_t		i;
	ssize_t		check;
	char		*line;
	char		*buffer;
}				t_variable;

// PROTOTYPES
char	*get_next_line(int fd);
char	*init_remainder(char *remain, char **buffer);
void	my_bzero(char *s, ssize_t n);
ssize_t	my_strlen(char *str);
char	*myy_strdup(char *str);
char	*dupl_and_adjust_remain(char *remain);
ssize_t	end_of_line(char *line);
char	*my_strjoin(char *s1, char *s2);
ssize_t	manage_extraction(int fd, char *buf, char **line);
char	extract_buffer(int fd, char *buffer);

#endif
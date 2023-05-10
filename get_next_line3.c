/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyk2 <donghyk2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:27:47 by donghyk2          #+#    #+#             */
/*   Updated: 2022/12/26 19:11:36 by donghyk2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	allfree(char **str)
{
	free(*str);
	*str = 0;
}

int	find_new_line_index(char *buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (-1);
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	add_line(char **buffer, int fd, int *readsize)
{
	char	*res;
	char	*newbuffer;

	newbuffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	*readsize = read(fd, newbuffer, BUFFER_SIZE);
	if (*readsize == 0)
	{
		allfree(&newbuffer);
		allfree(buffer);
		*buffer = NULL;
		return (0);
	}
	newbuffer[*readsize] = '\0';
	res = ft_strjoin(*buffer, newbuffer);
	allfree(buffer);
	allfree(&newbuffer);
	*buffer = res;
	return (1);
}

char	*eof(char **buffer)
{
	char	*line;

	if (ft_strlen(*buffer))
		line = ft_strdup(*buffer);
	else
		line = NULL;
	allfree(buffer);
	return (line);
}

#include <stdio.h>
char	*get_next_line(int fd)
{
	static char	*backup;
	char		*buffer;
	char		*line;
	int			linelen;
	int			readsize;

	readsize = 1;
	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
	{
		if (backup)
			allfree(&backup);
		return (0);
	}
	if (!backup)
		backup = ft_strdup("");
	buffer = ft_strdup(backup);
	allfree(&backup);
	while (add_line(&buffer, fd, &readsize) && find_new_line_index(buffer) == -1)
		if (readsize == 0)
			break ;
	if (readsize)
		linelen = find_new_line_index(buffer) + 1;
	else
		return (eof(&buffer));
	line = ft_substr(buffer, 0, linelen);
	backup = ft_substr(buffer, linelen, ft_strlen(buffer) - linelen);
	allfree(&buffer);
	return (line);
}

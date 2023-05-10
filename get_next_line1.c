/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyk2 <donghyk2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:59:22 by donghyk2          #+#    #+#             */
/*   Updated: 2022/12/21 23:43:24 by donghyk2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	allfree(char *str)
{
	free(str);
	str = 0;
}

int	find_new_line_index(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	ret_read_add_buffer(int fd, char **buffer)
{
	char	*newbuffer;
	char	*resbuffer;
	int		readsize;

	newbuffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!newbuffer)
		return (0);
	readsize = read(fd, newbuffer, BUFFER_SIZE);
	if (readsize == 0)
	{
		allfree(newbuffer);
		return (0);
	}
	newbuffer[readsize] = '\0';
	resbuffer = ft_strjoin(*buffer, newbuffer);
	allfree(newbuffer);
	allfree(*buffer);
	*buffer = resbuffer;
	return (readsize);
}

char	*ret_line(int fd, char **backup)
{
	char	*fullstr;
	char	*buffer;
	char	*line;
	int		readsize;
	int		linelen;

	buffer = ft_strdup("");
	readsize = ret_read_add_buffer(fd, &buffer);
	while (readsize && find_new_line_index(buffer) == -1)
		readsize = ret_read_add_buffer(fd, &buffer);
	if (!ft_strlen(*backup) && !ft_strlen(buffer))
	{
		allfree(*backup);
		allfree(buffer);
		return (0);
	}
	fullstr = ft_strjoin(*backup, buffer);
	allfree(*backup);
	allfree(buffer);
	linelen = find_new_line_index(fullstr) + 1;
	*backup = ft_substr(fullstr, linelen, ft_strlen(fullstr) - linelen);
	line = ft_substr(fullstr, 0, linelen);
	allfree(fullstr);
	return (line);
}

#include <stdio.h>
char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;
	char		*tmp;
	int			linelen;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
	{
		if (backup)
			allfree(backup);
		return (0);
	}
	if (!backup)
		backup = ft_strdup("");
	if (find_new_line_index(backup) == -1)
		return (ret_line(fd, &backup));
	linelen = find_new_line_index(backup) + 1;
	tmp = ft_substr(backup, linelen, ft_strlen(backup) - linelen);
	line = ft_substr(backup, 0, linelen);
	allfree(backup);
	backup = tmp;
	return (line);
}

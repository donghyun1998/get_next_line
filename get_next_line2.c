/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyk2 <donghyk2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:46:52 by donghyk2          #+#    #+#             */
/*   Updated: 2022/12/22 00:03:28 by donghyk2         ###   ########.fr       */
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

int	ret_read_add_buffer(int fd, char **backup)
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
	resbuffer = ft_strjoin(*backup, newbuffer);
	allfree(newbuffer);
	allfree(*backup);
	*backup = resbuffer;
	return (readsize);
}

char	*eof(char **backup)
{
	char	*line;

	if (ft_strlen(*backup))
		line = ft_strdup(*backup);
	else
		line = NULL;
	allfree(*backup);
	return (line);
}

char	*ret_line(int fd, char **backup)
{
	char	*tmp;
	char	*line;
	int		readsize;
	int		linelen;

	while (1)
	{
		readsize = ret_read_add_buffer(fd, backup);
		if (readsize == 0)
			break ;
		allfree(*backup);
		linelen = find_new_line_index(*backup) + 1;
		tmp = ft_substr(*backup, linelen, ft_strlen(*backup) - linelen);
		line = ft_substr(*backup, 0, linelen);
		allfree(*backup);
		*backup = tmp;
		return (line);
	}
	return (eof(backup));
}

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

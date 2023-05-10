/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyk2 <donghyk2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 13:58:34 by donghyk2          #+#    #+#             */
/*   Updated: 2023/01/18 19:48:44 by donghyk2         ###   ########.fr       */
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

char	*make_buf(int fd, int *eof_flag, char **backup)
{
	char	*buffer;
	int		readsize;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
	{
		allfree(&buffer);
		allfree(backup);
		*eof_flag = -1;
		return (0);
	}
	readsize = read(fd, buffer, BUFFER_SIZE);
	if (readsize == 0)
	{
		allfree(&buffer);
		*eof_flag = 1;
		return (0);
	}
	buffer[readsize] = '\0';
	if (readsize < BUFFER_SIZE)
		*eof_flag = 1;
	else
		*eof_flag = 0;
	return (buffer);
}

char	*make_line(char **backup)
{
	int		nl_idx;
	char	*line;
	char	*tmp;

	if (gnl_ft_strlen(*backup) == 0)
	{
		allfree(backup);
		return (0);
	}
	nl_idx = find_new_line_index(*backup);
	if (nl_idx == -1)
	{
		line = gnl_ft_strdup(*backup);
		allfree(backup);
		return (line);
	}
	line = gnl_ft_substr(*backup, 0, nl_idx + 1);
	tmp = gnl_ft_substr(*backup, nl_idx + 1, \
	gnl_ft_strlen(*backup) - nl_idx - 1);
	allfree(backup);
	*backup = tmp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*buffer;
	char		*tmp;
	int			eof_flag;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
	{
		if (backup)
			allfree(&backup);
		return (0);
	}
	if (!backup)
		backup = gnl_ft_strdup("");
	while (find_new_line_index(backup) == -1)
	{
		buffer = make_buf(fd, &eof_flag, &backup);
		tmp = gnl_ft_strjoin(backup, buffer);
		allfree(&backup);
		if (buffer)
			allfree(&buffer);
		backup = tmp;
		if (eof_flag)
			break ;
	}
	return (make_line(&backup));
}

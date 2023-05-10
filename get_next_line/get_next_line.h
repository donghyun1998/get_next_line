/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyk2 <donghyk2@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:27:50 by donghyk2          #+#    #+#             */
/*   Updated: 2023/02/18 18:20:50 by donghyk2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

size_t	gnl_ft_strlen(const char *s);
size_t	gnl_ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*gnl_ft_strdup(const char *s1);
char	*gnl_ft_strjoin(char const *s1, char const *s2);
char	*gnl_ft_substr(char const *s, unsigned int start, size_t len);
void	allfree(char **str);
int		find_new_line_index(char *buffer);
char	*make_buf(int fd, int *eof_flag, char **backup);
char	*make_line(char **backup);
char	*get_next_line(int fd);

#endif

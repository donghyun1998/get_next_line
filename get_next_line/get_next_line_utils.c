/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyk2 <donghyk2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:27:43 by donghyk2          #+#    #+#             */
/*   Updated: 2023/01/18 19:45:26 by donghyk2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	gnl_ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t			i;
	unsigned int	len;

	i = 0;
	len = 0;
	while (src[len])
		len++;
	if (dstsize == 0)
		return (len);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

char	*gnl_ft_strdup(const char *s1)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * (gnl_ft_strlen(s1) + 1));
	if (!res)
		return (0);
	gnl_ft_strlcpy(res, s1, gnl_ft_strlen(s1) + 1);
	return (res);
}

char	*gnl_ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	reslen;
	size_t	i;

	if (!s2)
		return (gnl_ft_strdup(s1));
	reslen = gnl_ft_strlen(s1) + gnl_ft_strlen(s2) + 1;
	res = (char *)malloc(sizeof(char) * reslen);
	if (!res)
		return (0);
	i = -1;
	while (++i < reslen - 1)
	{
		if (*s1)
			res[i] = *s1++;
		else
			res[i] = *s2++;
	}
	res[i] = '\0';
	return (res);
}

char	*gnl_ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	slen;

	if (!s)
		return (0);
	slen = gnl_ft_strlen(s);
	if (slen < start)
		return (gnl_ft_strdup(""));
	if (slen < start + len)
		len = slen - start;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	s += start;
	gnl_ft_strlcpy(res, s, len + 1);
	return (res);
}

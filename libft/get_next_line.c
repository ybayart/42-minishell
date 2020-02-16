/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 21:39:35 by ybayart           #+#    #+#             */
/*   Updated: 2019/11/18 19:12:11 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void		init_free_gnl(t_gnl *gnl, char **line)
{
	gnl->l_line = 0;
	*line = malloc(sizeof(char));
	*line[0] = 0;
}

int			gnl_is_readed(const char *s, int len)
{
	int	i;

	if (!s)
		return (-2);
	i = 0;
	while (i < len)
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int			gnl_lecture(int fd, t_gnl *gnl, char **line)
{
	gnl->len = read(fd, gnl->str, BUFFER_SIZE);
	if (gnl->len > 0)
		gnl->str[gnl->len] = '\0';
	if (gnl->len == 0)
		return (0);
	if (gnl->len == -1)
	{
		free(*line);
		return (-1);
	}
	return (1);
}

static char	*join(char *s1, char *s2, int *s_s1, int s_s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	if (!(str = malloc((*s_s1 + s_s2 + 1) * sizeof(char))))
		return (NULL);
	i = -1;
	while (++i < *s_s1)
		str[i] = s1[i];
	j = i;
	i = -1;
	while (++i < s_s2)
		str[j + i] = s2[i];
	*s_s1 += s_s2;
	str[j + i] = '\0';
	free(s1);
	return (str);
}

int			get_next_line(int fd, char **line)
{
	static t_gnl	gnl;
	char			*tmp;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, gnl.str, 0) == -1)
		return (-1);
	init_free_gnl(&gnl, line);
	if (gnl.i == 0 && (gnl.tmp = gnl_lecture(fd, &gnl, line)) <= 0)
		return (gnl.tmp);
	while (1)
	{
		if ((gnl.tmp = gnl_is_readed(gnl.str + gnl.i, gnl.len - gnl.i)) < 0)
			*line = join(*line, gnl.str + gnl.i, &gnl.l_line, gnl.len - gnl.i);
		else
		{
			tmp = ft_substr(gnl.str + gnl.i, 0, gnl.tmp);
			*line = join(*line, tmp, &gnl.l_line, gnl.tmp);
			free(tmp);
		}
		gnl.i = ((gnl.tmp < 0) ? 0 : gnl.i + gnl.tmp + 1);
		if (gnl.tmp >= 0)
			break ;
		if ((gnl.tmp = gnl_lecture(fd, &gnl, line)) <= 0)
			return (gnl.tmp);
	}
	return (1);
}

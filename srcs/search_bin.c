/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:29:43 by racohen           #+#    #+#             */
/*   Updated: 2020/01/16 11:42:15 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	search_path(const char *curr_dir, const char *path)
{
	int				fd;
	DIR				*dir_fd;
	struct dirent	*dir;

	if ((fd = open(path, O_RDONLY)) > 2)
	{
		close(fd);
		return (2);
	}
	if ((dir_fd = opendir(curr_dir)) == NULL)
		return (0);
	while ((dir = readdir(dir_fd)) != NULL)
	{
		if (ft_strlen(path) == ft_strlen((char*)dir->d_name) &&
			!strncmp(dir->d_name, path, ft_strlen(dir->d_name)))
		{
			closedir(dir_fd);
			return (1);
		}
	}
	closedir(dir_fd);
	return (0);
}

char		*search_bin(const char *path, const char *env_path)
{
	int		i;
	int		ret;
	char	*bin;
	char	*temp;
	char	**tmp;

	i = -1;
	bin = NULL;
	if ((tmp = ft_split(env_path, ':')) == NULL)
		return (NULL);
	while (tmp[++i])
	{
		if ((ret = search_path(tmp[i], path)) == 1)
		{
			temp = tmp[i];
			if ((tmp[i] = ft_strjoin(tmp[i], "/")) == NULL)
				return (NULL);
			free(temp);
			if ((bin = ft_strjoin(tmp[i], path)) == NULL)
				return (NULL);
			break ;
		}
		else if (ret == 2)
		{
			bin = ft_strdup(path);
			break;
		}
		else if (ft_get_len(tmp) == i -1)
			return (NULL);
	}
	ft_free_tab((void**)tmp);
	return (bin);
}

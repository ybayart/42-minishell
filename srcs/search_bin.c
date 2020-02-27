/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:29:43 by racohen           #+#    #+#             */
/*   Updated: 2020/02/27 02:17:36 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

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

int			search_bin_do(char **tmp, const char *path, char **bin, int i)
{
	int		ret;
	char	*temp;

	if ((ret = search_path(tmp[i], path)) == 1)
	{
		temp = tmp[i];
		if ((tmp[i] = ft_strjoin(tmp[i], "/")) == NULL)
			return (-1);
		free(temp);
		if ((*bin = ft_strjoin(tmp[i], path)) == NULL)
			return (-1);
		return (0);
	}
	else if (ret == 2)
	{
		*bin = ft_strdup(path);
		return (0);
	}
	else if (ft_get_len(tmp) == i - 1)
		return (-1);
	return (1);
}

char		*search_bin(const char *path, const char *env_path)
{
	int			i;
	char		*bin;
	char		**tmp;
	struct stat	buf;

	i = -1;
	bin = NULL;
	if (path[0] == '.' || path[0] == '/')
	{
		if (stat((bin = ft_strdup(path)), &buf) == 0 && buf.st_mode & S_IXUSR)
			return (bin);
		else
		{
			free(bin);
			return (NULL);
		}
	}
	if ((tmp = ft_split(env_path, ':')) == NULL)
		return (NULL);
	while (tmp[++i])
	{
		if (stat((bin = ft_strjoin_third(tmp[i], "/", path)), &buf) == 0 && buf.st_mode & S_IXUSR)
			break ;
		free(bin);
		bin = NULL;
	}
	ft_free_tab((void**)tmp);
	return (bin);
}

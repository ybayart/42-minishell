/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:29:43 by racohen           #+#    #+#             */
/*   Updated: 2020/01/24 17:12:19 by ybayart          ###   ########.fr       */
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
	int		i;
	int		ret;
	char	*bin;
	char	**tmp;

	i = -1;
	bin = NULL;
	if ((tmp = ft_split(env_path, ':')) == NULL)
		return (NULL);
	while (tmp[++i])
		if ((ret = search_bin_do(tmp, path, &bin, i)) == -1)
			return (NULL);
		else if (ret == 0)
			break ;
	ft_free_tab((void**)tmp);
	return (bin);
}

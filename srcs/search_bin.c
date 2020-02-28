/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:29:43 by racohen           #+#    #+#             */
/*   Updated: 2020/02/28 17:34:27 by yanyan           ###   ########.fr       */
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

char		test_bin(char *bin)
{
	struct stat	buf;

	stat(bin, &buf);
	if (S_ISREG(buf.st_mode) != 1)
		return (1);
	else if ((buf.st_mode & S_IXUSR) != 1)
		return (2);
	else
		return (0);
	return (3);
}

static void	print_error_bin(char err, char *bin)
{
	if (err == 1)
		print_error(1, "command not found", bin, NULL);
	else if (err == 2)
		print_error(1, "No such file or directory", bin, NULL);
	else if (err == 3)
		print_error(1, "Permission denied", bin, NULL);
}

char		*search_bin(char *path, const char *env_path)
{
	int			i;
	char		ret;
	char		*bin;
	char		**tmp;

	i = -1;
	bin = NULL;
	ret = 0;
	if (path[0] == '.' || path[0] == '/')
	{
		print_error_bin((ret = test_bin(path)), path);
		if (ret == 0)
			return (NULL);
		return (path);
	}
	if ((tmp = ft_split(env_path, ':')) == NULL)
		return (NULL);
	while (tmp[++i])
	{
		bin = ft_strjoin_third(tmp[i], "/", path);
		if ((ret = test_bin(bin)) == 0)
			break ;
		if (ret >= 2)
		{
			print_error_bin(ret, bin);
			free(bin);
			return ((bin = NULL));
		}
		free(bin);
		bin = NULL;
	}
	if (ret != 1)
		print_error_bin(0, path);
	ft_free_tab((void**)tmp);
	return (bin);
}

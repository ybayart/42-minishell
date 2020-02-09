/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 17:01:00 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/09 13:54:06 by yanyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		g_nb;

static char	test_wildcard(char str[], char pattern[], int n, int m)
{
	int		i;
	int		j;
	char	res[n + 1][m + 1];

	if (m == 0)
		return (n == 0);
	ft_memset(res, 0, sizeof(res));
	res[0][0] = 1;
	j = 0;
	while (++j <= m)
		if (pattern[j - 1] == '*')
			res[0][j] = res[0][j - 1];
	i = 0;
	while (++i <= n)
	{
		j = 0;
		while (++j <= m)
			if (pattern[j - 1] == '*')
				res[i][j] = res[i][j - 1] || res[i - 1][j];
			else if (str[i - 1] == pattern[j - 1])
				res[i][j] = res[i - 1][j - 1];
			else
				res[i][j] = 0;
	}
	return (res[n][m]);
}

static char	list_dir(char ***search, int pos, char *path[3])
{
	DIR				*dir_fd;
	struct dirent	*dir;
	char			state;
	struct stat		buf;
	char			*file;

	if ((dir_fd = opendir(path[0])) == NULL)
		return (0);
	state = 0;
	while ((dir = readdir(dir_fd)) != NULL)
		if (ft_strncmp(dir->d_name, ".", 1) != 0)
			if (test_wildcard(dir->d_name, path[2], ft_strlen(dir->d_name),
							ft_strlen(path[2])) == 1)
			{
				stat((file = ft_strjoin(path[0], dir->d_name)), &buf);
				if (path[1][0] == '\0' || S_ISDIR(buf.st_mode))
				{
					file = ft_strjoin(file, path[1]);
					if (state == 0 && ((*search)[pos] = file) == NULL)
						return (0);
					if (state == 1 && ((*search) =
						ft_strinsert((*search), file, pos++)) == NULL)
						return (0);
					state = 1;
					g_nb++;
				}
			}
	closedir(dir_fd);
	if (g_nb == 0)
		return (0);
	return (1);
}

char		wildcard(char ***args, int *pos, int initpos)
{
	int		i;
	char	replace;
	char	**search;
	char	*path[3];
	char	*last;

	search = NULL;
	if ((search = addstr(search)) == NULL)
		return (0);
	search[0] = (*args)[initpos];
	replace = 0;
	if (ft_strncmp(search[0], "/", 1) != 0 &&
	ft_strncmp(search[0], "./", 2) != 0 && ft_strncmp(search[0], "../", 3) != 0)
		replace = 1;
	i = 0;
	g_nb = 0;
	last = NULL;
	while (search[i] != 0)
	{
		if (ft_strchr(search[i], '*') == NULL || (last != NULL && ft_strcmp(search[i], last) == 0))
			i++;
		else
		{
			path[0] = w_getrootdir(search[i]);
			path[1] = w_getchilddir(search[i]);
			path[2] = w_getpattern(search[i]);
			if (list_dir(&search, i, path) == 0)
				break ;
			last = search[i];
		}
	}
	if (g_nb != 0)
	{
		ft_sort_string_tab(search);
		initpos = i;
		i = -1;
		while (search[++i] != 0)
			if (replace == 1)
			{
				last = search[i];
				search[i] = ft_strdup(search[i] + 2);
				free(last);
			}
		i = -1;
		while (++i < (*pos))
			if ((search = ft_strinsert(search, (*args)[i], i)) == NULL)
				return (0);
		free((*args));
		(*args) = search;
		(*pos) += initpos;
		(*args) = addstr((*args));
	}
	return (1);
}

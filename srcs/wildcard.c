/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 17:01:00 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/03 18:03:57 by ybayart          ###   ########.fr       */
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

static char	*getrootdir(char *str)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] != '/' && str[i] != '\0')
		i++;
	j = 0;
	while (str[j] != '*' && str[j] != '\0')
		j++;
	if (i > j)
		return (ft_strdup("./"));
	else
	{
		if (ft_strncmp(str, "/", 1) != 0 && ft_strncmp(str, "./", 2) != 0
										&& ft_strncmp(str, "../", 3) != 0)
		{
			return (ft_strjoin("./", ft_strndup(str,
				ft_strnlastpos(str, '/', j) + 1)));
		}
		return (ft_strndup(str, ft_strnlastpos(str, '/', j) + 1));
	}
}

static char	*getchilddir(char *str)
{
	int		i;
	int		j;
	char	*newstr;

	i = -1;
	while (str[++i] != '\0')
		if (str[i] == '*')
			break ;
	if (str[i] == '\0')
		return (ft_strdup(""));
	while (str[++i] != '\0')
		if (str[i] == '/')
			break ;
	if (str[i] == '\0')
		return (ft_strdup(""));
	if ((newstr = malloc(sizeof(char) * (ft_strlen(str) - i + 1))) == NULL)
		return (NULL);
	j = i;
	while (str[i] != '\0')
	{
		newstr[i - j] = str[i];
		i++;
	}
	newstr[i - j] = '\0';
	return (newstr);
}

static char	*getpattern(char *str)
{
	int		i;
	int		j;
	char	*newstr;

	i = -1;
	while (str[++i] != '\0')
		if (str[i] == '*')
			break ;
	i++;
	while (--i >= 0)
		if (str[i] == '/')
			break ;
	j = i++;
	while (str[++j] != '\0')
		if (str[j] == '/')
			break ;
	newstr = ft_strndup(str + i, (size_t)j - i);
	return (newstr);
}

char		wildcard(char ***args, int *pos, int initpos)
{
	int		i;
	char	**search;
	char	*path[3];

	search = NULL;
	if ((search = addstr(search)) == NULL)
		return (0);
	search[0] = (*args)[initpos];
	i = 0;
	g_nb = 0;
	while (search[i] != 0)
	{
		if (ft_strchr(search[i], '*') == NULL)
			i++;
		else
		{
			path[0] = getrootdir(search[i]);
			path[1] = getchilddir(search[i]);
			path[2] = getpattern(search[i]);
			if (list_dir(&search, i, path) == 0)
				break ;
		}
	}
	if (g_nb != 0)
	{
		ft_sort_string_tab(search);
		initpos = i;
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

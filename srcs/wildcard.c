/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 17:01:00 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/09 19:18:01 by yanyan           ###   ########.fr       */
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

static char	list_dir(t_list **search, char *path[3])
{
	DIR				*dir_fd;
	struct dirent	*dir;
	struct stat		buf;
	char			*file;
	t_list			*newlst;

	if ((dir_fd = opendir(path[0])) == NULL)
		return (0);
	g_nb = 0;
	newlst = NULL;
	while ((dir = readdir(dir_fd)) != NULL)
		if (ft_strncmp(dir->d_name, ".", 1) != 0)
			if (test_wildcard(dir->d_name, path[2], ft_strlen(dir->d_name),
							ft_strlen(path[2])) == 1)
			{
				stat((file = ft_strjoin(path[0], dir->d_name)), &buf);
				if (path[1][0] == '\0' || S_ISDIR(buf.st_mode))
				{
					file = ft_strjoin(file, path[1]);
					ft_lstadd_back(&newlst, ft_lstnew(file));
					g_nb++;
				}
			}
	closedir(dir_fd);
	if (g_nb == 0)
		return (0);
	ft_lstlast(newlst)->next = (*search)->next;
	(*search)->content = newlst->content;
	(*search)->next = newlst->next;
	return (1);
}

char		wildcard(char ***args, int *pos, int initpos)
{
	int		i;
	char	replace;
	t_list	*search;
	t_list	*tmp;
	char	*path[3];
	char	breaking;
	char	**newstr;
	size_t	len;

	if ((search = ft_lstnew((*args)[initpos])) == NULL)
		return (0);
	replace = 0;
	if (ft_strncmp(search->content, "/", 1) != 0 && ft_strncmp(search->content,
					"./", 2) != 0 && ft_strncmp(search->content, "../", 3) != 0)
		replace = 1;
	g_nb = 0;
	while (1)
	{
		breaking = 1;
		tmp = search;
		while (tmp != NULL)
		{
			if (strchr(tmp->content, '*') != NULL)
			{
				path[0] = w_getrootdir(tmp->content);
				path[1] = w_getchilddir(tmp->content);
				path[2] = w_getpattern(tmp->content);
				if (list_dir(&tmp, path) == 0)
					break ;
				breaking = 0;
			}
			tmp = tmp->next;
		}
		if (breaking == 1)
			break ;
	}
	if (g_nb != 0)
	{
		ft_lst_sort(&search, ft_strcmp);
		tmp = search;
		while (tmp != NULL)
		{
			if (replace == 1)
			{
				path[0] = tmp->content;
				tmp->content = ft_strdup(tmp->content + 2);
				free(path[0]);
			}
			tmp = tmp->next;
		}
		len = ft_lstsize(search);
		if ((newstr = malloc(sizeof(char*) * (ft_tablen((const char**)(*args)) + len + 1))) == NULL)
			return (0);
		i = -1;
		while (++i < (*pos))
			newstr[i] = (*args)[i];
		tmp = search;
		while (tmp != NULL)
		{
			newstr[i++] = tmp->content;
			tmp = tmp->next;
		}
		while ((*args)[(size_t)++i - len] != 0)
			newstr[i] = (*args)[(size_t)i - len];
		newstr[i - 1] = 0;
		free(*args);
		(*args) = newstr;
		(*pos) = i - 2;
	}
	return (1);
}

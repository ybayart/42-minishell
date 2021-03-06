/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 17:01:00 by ybayart           #+#    #+#             */
/*   Updated: 2020/03/26 17:52:54 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		g_nb;

void		test_dir(struct dirent *dir, char *path[3], t_list **newlst, int *i)
{
	char		*file;
	struct stat	buf;

	if (ft_strncmp(dir->d_name, ".", 1) != 0 || path[2][0] == '.')
		if (test_wildcard(dir->d_name, path[2], ft_strlen(dir->d_name),
						ft_strlen(path[2])) == 1)
		{
			stat((file = ft_strjoin(path[0], dir->d_name)), &buf);
			if (path[1][0] == '\0' || S_ISDIR(buf.st_mode))
			{
				file = ft_strfjoin(file, path[1]);
				ft_lstadd_back(newlst, ft_lstnew(file));
				g_nb++;
				(*i)++;
			}
			else
				free(file);
		}
}

void		wildcard_do_getdir(t_list **search)
{
	t_list	*tmp;
	char	*path[3];
	char	breaking;

	g_nb = 0;
	while (1 && (breaking = 1))
	{
		tmp = (*search);
		while (tmp != NULL)
		{
			if (ft_strchr(tmp->content, '*') != NULL)
			{
				path[0] = w_getrootdir(tmp->content);
				path[1] = w_getchilddir(tmp->content);
				path[2] = w_getpattern(tmp->content);
				breaking = (list_dir(&tmp, path) == 1) ? 0 : breaking;
				free(path[0]);
				free(path[1]);
				free(path[2]);
			}
			tmp = tmp->next;
		}
		if (breaking == 1)
			break ;
	}
}

void		wildcard_do_format(t_list **search, char replace)
{
	t_list		*tmp;
	int			i;
	char		*str;
	struct stat	buf;

	ft_lst_sort(search, ft_strcmp);
	tmp = (*search);
	i = 0;
	while (tmp != NULL)
	{
		if (replace == 1)
		{
			str = ft_strdup(tmp->content + 2);
			free(tmp->content);
			tmp->content = str;
		}
		if (ft_strchr(tmp->content, '*') != NULL ||
			stat(tmp->content, &buf) != 0)
		{
			ft_lstdel_at(search, i);
			tmp = ft_lstget_at((*search), i);
		}
		else if (++i != 0)
			tmp = tmp->next;
	}
}

int			wildcard_do_concat(t_list **search, int *pos, char ***args)
{
	size_t	len;
	t_list	*tmp;
	char	**newstr;
	int		i;

	len = ft_lstsize((*search));
	if ((newstr = malloc(sizeof(char*) *
		(ft_tablen((const char**)(*args)) + len + 1))) == NULL)
		return (-1);
	i = -1;
	(*pos) = (len == 0 ? (*pos) + 1 : (*pos));
	while (++i < (*pos))
		newstr[i] = (*args)[i];
	tmp = (*search);
	while (tmp != NULL)
	{
		newstr[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	while ((*args)[(size_t)++i - (len + 1)] != 0 &&
			(*args)[(size_t)i - len] != 0)
		newstr[i] = (*args)[(size_t)i - len];
	free((*args));
	(*args) = newstr;
	return (i);
}

char		wildcard(char ***args, int *pos, int initpos)
{
	t_wildcard	d;

	d.arg = ft_strdup((*args)[initpos]);
	if (init_wildcard(&(d.search), args, initpos, &(d.replace)) == 0)
		return (0);
	wildcard_do_getdir(&(d.search));
	if (g_nb != 0)
	{
		free((*args)[initpos]);
		wildcard_do_format(&(d.search), d.replace);
		if ((d.i = wildcard_do_concat(&(d.search), pos, args)) == -1)
		{
			free(d.arg);
			ft_lstclear(&(d.search));
			return (0);
		}
		(ft_lstsize(d.search) == 0 ? (*args)[initpos] = d.arg : free(d.arg));
		(*args)[d.i - 1] = 0;
		(*pos) = d.i - 2;
	}
	else
		free(d.arg);
	ft_lstclear(&(d.search));
	return (1);
}

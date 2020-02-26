/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 23:17:12 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/26 14:42:12 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	list_dir(t_list **search, char *path[3])
{
	DIR				*dir_fd;
	struct dirent	*dir;
	t_list			*newlst;
	int				i;

	if ((dir_fd = opendir(path[0])) == NULL)
		return (0);
	newlst = NULL;
	i = 0;
	while ((dir = readdir(dir_fd)) != NULL)
		test_dir(dir, path, &newlst, &i);
	closedir(dir_fd);
	if (i == 0)
		return (0);
	ft_lstlast(newlst)->next = (*search)->next;
	free((*search)->content);
	(*search)->content = newlst->content;
	(*search)->next = newlst->next;
	free(newlst);
	return (1);
}

char	test_wildcard(char str[], char pattern[], int n, int m)
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

char	*w_getrootdir(char *str)
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
			return (ft_strffjoin("./", ft_strndup(str,
				ft_strnlastpos(str, '/', j) + 1)));
		}
		return (ft_strndup(str, ft_strnlastpos(str, '/', j) + 1));
	}
}

char	*w_getchilddir(char *str)
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

char	*w_getpattern(char *str)
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

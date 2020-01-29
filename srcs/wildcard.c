/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 17:01:00 by ybayart           #+#    #+#             */
/*   Updated: 2020/01/29 16:59:33 by yanyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

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

static char	list_dir(char ***args, int *pos, char *curr_dir, char *pattern)
{
	DIR				*dir_fd;
	struct dirent	*dir;
 
	if ((dir_fd = opendir(curr_dir)) == NULL)
	{
		printf("error 1 |%s|\n", curr_dir);
		return (0);
	}
	while ((dir = readdir(dir_fd)) != NULL)
	{
		if (ft_strcmp(dir->d_name, ".") != 0 && ft_strcmp(dir->d_name, "..") != 0)
		{
			if (test_wildcard(dir->d_name, pattern, ft_strlen(dir->d_name), ft_strlen(pattern)) == 1)
			{
//		    	stat(dir->d_name, &buf);
//				if (S_ISDIR(buf.st_mode))
//				{
//					if (list_dir(args, pos, ft_strjoin(curr_dir, dir->d_name), pattern) == 0)
//						return (0);
//				}
//				else
					printf("+ %s\n", ft_strjoin(curr_dir, dir->d_name));
			}
		}
	}
	(void)args;
	(void)pos;
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
		if (ft_strncmp(str, "/", 1) != 0 && ft_strncmp(str, "./", 2) != 0 && ft_strncmp(str, "../", 3) != 0)
			return (ft_strjoin("./", ft_strndup(str, ft_strnlastpos(str, '/', j) + 1)));
		return (ft_strndup(str, ft_strnlastpos(str, '/', j) + 1));
	}
}

static char	*getafterroot(char *str)
{
	int		i;
	int		j;
	char	*newstr;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '*')
			break ;
	}
	if (str[i] == '\0')
		return (ft_strdup(""));
	while (str[++i] != '\0')
	{
		if (str[i] == '/')
			break ;
	}
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

char		wildcard(char ***args, int *pos, int initpos)
{
	int				i;
//	size_t			j;
//	char			*strdir;
//	DIR				*dir_fd;
//	struct dirent	*dir;

	i = initpos - 1;
	while ((*args)[++i] != 0)
	{
		if (ft_strchr((*args)[i], '*') == NULL)
			printf("|%s| good\n", (*args)[i]);
		else
		{
			printf("|%s|\n - root: |%s|\n - after: |%s|\n", (*args)[i], getrootdir((*args)[i]), getafterroot((*args)[i]));
		}
//		if (ft_strchr((*args)[i], '*') == NULL)
//			printf("+ %s\n", (*args)[i]);
//		else
//		{
//			j = 0;
//			while ((*args)[(*pos)][j] != '/' && (*args)[(*pos)][j] != '\0')
//				j++;
//			char	*after = ft_strchr((*args)[(*pos)] + j + 1, '/');
//			strdir = ((*args)[(*pos)][j] != '/' ? ft_strdup("./") : ft_strndup((*args)[(*pos)], j + 1));
//			if ((dir_fd = opendir(strdir)) == NULL)
//				return (0);
//			while ((dir = readdir(dir_fd)) != NULL)
//			{
//				if (dir->d_name[0] != '.')
//				{
//					char	*tmp = ft_strjoin(strdir, dir->d_name);
//					if (after != 0)
//						tmp = ft_strjoin(tmp, after);
//					printf("add %s at %d\n", tmp, (*pos));
//					(*args)[(*pos)++] = tmp;
//					(*args) = addstr((*args));
//					if (wildcard(args, pos) == 0)
//						return (0);
//				}
//			}
//		}
	}
	printf("wildcard: %s (%d)\n", (*args)[(*pos)], (*pos));
	(void)list_dir;
	return (1);
}

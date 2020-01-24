/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 17:01:00 by ybayart           #+#    #+#             */
/*   Updated: 2020/01/24 19:33:13 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"

char	strmatch(char *str, char *pattern, int n, int m)
{
	int		i;
	int		j;
	char	lookup[n + 1][m + 1];

	if (m == 0)
		return (n == 0);
	ft_memset(lookup, 0, sizeof(lookup));
	lookup[0][0] = 1;
	j = 0;
	while (++j <= m)
		if (pattern[j - 1] == '*')
			lookup[0][j] = lookup[0][j - 1];
	i = 0;
	while (++i <= n)
	{
		j = 0;
		while (++j <= m)
		{
			if (pattern[j - 1] == '*')
				lookup[i][j] = lookup[i][j - 1] || lookup[i - 1][j];
			else if (pattern[j - 1] == '?' || str[i - 1] == pattern[j - 1])
				lookup[i][j] = lookup[i - 1][j - 1];
			else lookup[i][j] = 0;
		}
	}
	return (lookup[n][m]); 
}

/*
**int		main(int argc, char **argv)
**{
**	DIR				*dir_fd;
**	struct dirent	*dir;
**	int				i;
**	int				j;
**	char			skip;
**
**	if (argc < 2)
**		write(2, "missing argument\n", 17);
**	else
**	{
**		dir_fd = opendir("./");
**		while ((dir = readdir(dir_fd)) != NULL)
**		{
**			if (ft_strcmp(dir->d_name, ".") != 0 && ft_strcmp(dir->d_name, "..") != 0)
**			{
**				if (strmatch(dir->d_name, argv[1], ft_strlen(dir->d_name), ft_strlen(argv[1])))
**					printf("%s\n", dir->d_name);
**				printf("%s\n", dir->d_name);
**				i = 0;
**				j = 0;
**				while (argv[1][i] != '\0')
**				{
**					skip = 0;
**					while (argv[1][i] == '*')
**					{
**						i++;
**						skip = 1;
**					}
**					if (skip == 1 || argv[1][i] == '\0')
**					{
**						while (dir->d_name[j] != argv[1][i] && dir->d_name[j] != '\0')
**							j++;
**					}
**					printf(" - skip: %d / %c / %c\n", skip, argv[1][i], dir->d_name[j]);
**					if (dir->d_name[j] != argv[1][i] || (dir->d_name[j] == '\0' && argv[1][i] == '\0'))
**						break ;
**					i++;
**					j++;
**				}
**				printf(" - %c / %c\n", argv[1][i], dir->d_name[j]);
**				if (argv[1][i] == '\0' && dir->d_name[j] == '\0')
**					printf("%s\n", dir->d_name);
**			}
**		}
**	}
**}
*/

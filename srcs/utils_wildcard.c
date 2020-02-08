/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 23:17:12 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/08 23:18:22 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

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
			return (ft_strjoin("./", ft_strndup(str,
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

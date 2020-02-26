/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:07:48 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/13 18:41:36 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_tabintlen(int *ft_tab)
{
	size_t		i;

	i = 0;
	while (ft_tab[i] != -1)
		i++;
	return (i);
}

static int		*addindex(int *index, int value)
{
	int		i;
	size_t	len;
	int		*new;

	len = ft_tabintlen(index);
	if ((new = malloc(sizeof(int) * (len + 2))) == NULL)
		return (NULL);
	new[len + 1] = -1;
	new[len] = value;
	i = -1;
	while (index[++i] != -1)
		new[i] = index[i];
	free(index);
	return (new);
}

static int		*getindex(char *str, char *search)
{
	int		i;
	int		j;
	size_t	len;
	int		*index;

	len = ft_strlen(search);
	i = -1;
	if ((index = malloc(sizeof(int))) == NULL)
		return (NULL);
	index[0] = -1;
	while (str[++i])
	{
		if (str[i] == search[0])
		{
			j = 0;
			while (search[j] && str[i + j] == search[j])
				j++;
			if ((size_t)j == len)
			{
				index = addindex(index, i);
				i += len - 1;
			}
		}
	}
	return (index);
}

static void		clearall(char **str, char *search, char *replace, int *index)
{
	free(*str);
	free(search);
	free(replace);
	free(index);
}

char			*ft_strreplace(char **str, char *search, char *replace)
{
	int		i[4];
	char	*tmp;
	int		*index;

	index = getindex(*str, search);
	if ((tmp = malloc(sizeof(char) * (ft_strlen(*str) - ft_tabintlen(index)
			* (ft_strlen(replace) - ft_strlen(replace)) + 1))) == NULL)
		return (ft_freeint(index));
	i[0] = -1;
	i[1] = 0;
	i[3] = 0;
	while ((*str)[++i[0]])
		if (i[0] == index[i[3]] && i[3]++ != -1 && (i[2] = -1) == -1)
		{
			while (replace[++i[2]])
				tmp[i[1]++] = replace[i[2]];
			i[0] += ft_strlen(search) - 1;
		}
		else
			tmp[i[1]++] = (*str)[i[0]];
	tmp[i[1]] = '\0';
	clearall(str, search, replace, index);
	*str = tmp;
	return (*str);
}

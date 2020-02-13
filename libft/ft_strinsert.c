/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 21:16:37 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/13 18:40:56 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strinsert(char **list, char *str, size_t pos)
{
	int		i;
	size_t	len;
	char	**newtab;

	if (pos > (len = ft_tablen((const char **)list)) || str == NULL)
		return (NULL);
	if ((newtab = malloc(sizeof(char *) * (len + 2))) == NULL)
		return (NULL);
	i = -1;
	while ((size_t)++i < pos)
		newtab[i] = list[i];
	newtab[i] = str;
	while (list[++i - 1] != 0)
		newtab[i] = list[i - 1];
	newtab[i] = 0;
	free(list);
	return (newtab);
}

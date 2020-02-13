/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:15:30 by racohen           #+#    #+#             */
/*   Updated: 2020/02/14 00:36:33 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_cat(char *dest, const char *src, int lens1, int lens2)
{
	int i;

	i = 0;
	while (i < lens2)
	{
		dest[lens1 + i] = src[i];
		i++;
	}
	dest[lens1 + i] = '\0';
	return (dest);
}

static char	*ft_cpy(char *dest, const char *src, int lens1)
{
	int i;

	i = 0;
	while (i < lens1)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

char		*ft_strjoinfreeboth(char *s1, char *s2, int l1, int l2)
{
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if ((str = malloc(l1 + l2 + 1)) == NULL)
		return (NULL);
	ft_cpy(str, s1, l1);
	ft_cat(str, s2, l1, l2);
	free(s1);
	free(s2);
	return (str);
}

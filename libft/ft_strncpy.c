/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:55:12 by racohen           #+#    #+#             */
/*   Updated: 2020/01/16 15:21:17 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, char const *src, size_t n)
{
	size_t i;

	i = -1;
	if (dst == NULL || src == NULL)
		return (NULL);
	while (++i < n && src[i])
		dst[i] = src[i];
	while (i < n--)
		dst[i] = '\0';
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 11:07:01 by racohen           #+#    #+#             */
/*   Updated: 2019/11/18 16:02:40 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t size_src;

	size_src = ft_strlen(src);
	if (size_src < dstsize)
	{
		ft_strncpy(dest, src, size_src);
	}
	else if (dstsize != 0)
	{
		ft_strncpy(dest, src, dstsize - 1);
		dest[dstsize - 1] = '\0';
	}
	return (size_src);
}

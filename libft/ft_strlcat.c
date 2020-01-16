/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 19:48:13 by racohen           #+#    #+#             */
/*   Updated: 2019/11/04 20:25:03 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len_dest;
	size_t	k;
	size_t	len_src;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	if (size == 0)
		return (len_src);
	if (size < len_dest)
		len_src += size;
	else
		len_src += len_dest;
	k = 0;
	while (src[k] != '\0' && (len_dest + k) < size - 1)
	{
		dest[len_dest + k] = src[k];
		k++;
	}
	dest[len_dest + k] = '\0';
	return (len_src);
}

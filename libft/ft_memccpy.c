/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:40:24 by racohen           #+#    #+#             */
/*   Updated: 2019/11/05 21:38:37 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*t1;
	unsigned char	*t2;
	size_t			i;

	i = 0;
	t1 = (unsigned char *)dest;
	t2 = (unsigned char *)src;
	while (i < n)
	{
		t1[i] = t2[i];
		if (t1[i] == (unsigned char)c)
			return ((void*)(dest + i + 1));
		++i;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:38:25 by racohen           #+#    #+#             */
/*   Updated: 2019/11/06 15:18:58 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*pdst;
	unsigned char	*psrc;
	size_t			i;

	i = 0;
	if (src == NULL && dest == NULL)
		return (NULL);
	pdst = (unsigned char *)dest;
	psrc = (unsigned char *)src;
	while (i < n)
	{
		*pdst = *psrc;
		i++;
		pdst++;
		psrc++;
	}
	return (dest);
}

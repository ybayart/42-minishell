/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:49:36 by racohen           #+#    #+#             */
/*   Updated: 2019/11/06 04:20:07 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*sptr;
	unsigned char	*dptr;

	sptr = (unsigned char *)src;
	dptr = (unsigned char *)dest;
	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (sptr < dptr)
		while (++i <= n)
			dptr[n - i] = sptr[n - i];
	else
		while (n-- > 0)
			*(dptr++) = *(sptr++);
	return (dest);
}

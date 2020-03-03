/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_third.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:08:20 by ybayart           #+#    #+#             */
/*   Updated: 2020/03/03 20:46:25 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_third(const char *s1, const char *s2, const char *s3)
{
	size_t	size;
	size_t	i;
	size_t	j;
	size_t	k;
	char	*dst;

	if (s1 == NULL || s2 == NULL || s3 == NULL)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	if ((dst = ft_calloc(sizeof(char), size)) == NULL)
		return (NULL);
	i = -1;
	while (*(s1 + ++i))
		*(dst + i) = *(s1 + i);
	j = -1;
	while (*(s2 + ++j))
		*(dst + i + j) = *(s2 + j);
	k = -1;
	while (*(s3 + ++k))
		*(dst + i + j + k) = *(s3 + k);
	*(dst + i + j + k) = '\0';
	return (dst);
}

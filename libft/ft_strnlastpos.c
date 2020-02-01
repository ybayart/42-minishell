/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlastpos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 19:10:52 by yanyan            #+#    #+#             */
/*   Updated: 2020/01/27 19:35:12 by yanyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnlastpos(const char *str, char c, int n)
{
	size_t		i;

	if (n < 0)
		return (0);
	i = ft_strlen(str);
	if (i > (size_t)n)
		i = n;
	while (i != 0)
	{
		if (str[i] == c)
			break ;
		i--;
	}
	return (i);
}

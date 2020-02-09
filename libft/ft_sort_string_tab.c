/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_string_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 10:41:57 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/09 16:56:03 by yanyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_string_tab(char **tab)
{
	size_t	i1;
	size_t	i2;
	char	*tmp;
	size_t	len;

	i1 = 0;
	len = ft_tablen((const char **)tab);
	while (i1 < len)
	{
		i2 = 0;
		while (++i2 < len - 1)
		{
			if (ft_strcmp(tab[i2], tab[i2 - 1]) < 0)
			{
				tmp = tab[i2];
				tab[i2] = tab[i2 - 1];
				tab[i2 - 1] = tmp;
			}
		}
		i1++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_string_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 10:41:57 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/13 18:40:30 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_string_tab(char **ft_tab)
{
	size_t	i1;
	size_t	i2;
	char	*tmp;
	size_t	len;

	i1 = 0;
	len = ft_tablen((const char **)ft_tab);
	while (i1 < len)
	{
		i2 = 0;
		while (++i2 < len - 1)
		{
			if (ft_strcmp(ft_tab[i2], ft_tab[i2 - 1]) < 0)
			{
				tmp = ft_tab[i2];
				ft_tab[i2] = ft_tab[i2 - 1];
				ft_tab[i2 - 1] = tmp;
			}
		}
		i1++;
	}
}

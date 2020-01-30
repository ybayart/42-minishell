/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_string_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 10:41:57 by ybayart           #+#    #+#             */
/*   Updated: 2020/01/30 20:15:08 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_string_tab(char **tab)
{
	int		i;
	int		end;
	char	*tmp;

	end = 0;
	while (end == 0)
	{
		end = 1;
		i = -1;
		while (tab[++i + 1])
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				end = 0;
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
			}
		}
	}
}

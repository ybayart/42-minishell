/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_tab_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 09:31:23 by racohen           #+#    #+#             */
/*   Updated: 2020/01/16 15:20:52 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	**ft_list_to_tab_env(t_list_env *list)
{
	char	**res;
	int		size;

	size = ft_lst_size_env(list);
	if ((res = (char**)malloc(sizeof(char*) * (size + 1))) == NULL)
		return (NULL);
	res[size] = 0;
	size = -1;
	while (list != NULL)
	{
		res[++size] = ft_strjoin_third(list->name, "=", list->value);
		list = list->next;
	}
	return (res);
}

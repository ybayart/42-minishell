/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_tab_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 09:31:23 by racohen           #+#    #+#             */
/*   Updated: 2019/11/30 09:49:37 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_env.h"

char	**ft_list_to_tab_env(t_list_env *list)
{
	char	**res;
	char	*tmp;
	int		size;

	size = ft_lst_size_env(list);
	if ((res = (char**)malloc(sizeof(char*) * (size + 1))) == NULL)
		return (NULL);
	res[size] = 0;
	size = -1;
	while (list)
	{
		if ((res[++size] = ft_calloc(
			(ft_strlen(list->name) + ft_strlen(list->value) + 2), sizeof(char))) == NULL)
			return (NULL);
		res[size] = ft_strjoin(list->name, "=");
		tmp = res[size];
		res[size] = ft_strjoin(res[size], list->value);
		free(tmp);
		list = list->next;
	}
	return (res);
}

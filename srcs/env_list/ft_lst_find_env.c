/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_find_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:27:06 by racohen           #+#    #+#             */
/*   Updated: 2019/11/30 12:01:26 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_env.h"

char	*ft_lst_find_env(t_list_env **list, char *name)
{
		t_list_env	*tmp;

		if (!list || !(*list))
			return (NULL);
		tmp = *list;
		while (tmp->next)
		{
			if (ft_strncmp(tmp->name, name, ft_strlen(name)) == 0)
				return (tmp->value);
			tmp = tmp->next;
		}
		return (NULL);
}

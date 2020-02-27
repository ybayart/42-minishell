/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_get_at_typed.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:07:39 by racohen           #+#    #+#             */
/*   Updated: 2020/02/27 15:23:07 by yanyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_typed	*ft_lst_get_at_typed(t_typed *lst, int at)
{
	int i;

	i = 0;
	while (lst)
	{
		if (i == at)
			return (lst);
		lst = lst->next;
		i++;
	}
	return (NULL);
}

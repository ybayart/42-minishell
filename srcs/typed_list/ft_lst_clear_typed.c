/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_clear_typed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:39:17 by racohen           #+#    #+#             */
/*   Updated: 2020/02/13 22:59:07 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_lst_clear_typed(t_typed **lst)
{
	t_typed	*tmp;
	t_typed	*list;

	list = *lst;
	tmp = NULL;
	while (list != NULL)
	{
		if (list->next)
			tmp = list->next;
		else
			tmp = NULL;
		free(list);
		list = tmp;
	}
	*lst = NULL;
}

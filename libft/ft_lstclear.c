/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 21:00:14 by racohen           #+#    #+#             */
/*   Updated: 2020/02/16 16:32:26 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;
	t_list	*list;

	list = *lst;
	tmp = NULL;
	while (list != NULL)
	{
		if (list->next)
			tmp = list->next;
		else
			tmp = NULL;
		if (list->content != NULL)
			free(list->content);
		free(list);
		list = tmp;
	}
	*lst = NULL;
}

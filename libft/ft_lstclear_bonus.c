/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 21:00:14 by racohen           #+#    #+#             */
/*   Updated: 2019/11/29 16:46:15 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*list;

	list = *lst;
	tmp = NULL;
	while (list != NULL && del != NULL)
	{
		if (list->next)
			tmp = list->next;
		else
			tmp = NULL;
		if (list->content != NULL)
			(*del)(list->content);
		free(list);
		list = tmp;
	}
	*lst = NULL;
}

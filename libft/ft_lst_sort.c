/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 20:08:29 by ybayart           #+#    #+#             */
/*   Updated: 2020/03/03 20:44:26 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_swap(t_list *list)
{
	void	*content;

	content = list->content;
	list->content = list->next->content;
	list->next->content = content;
}

void	ft_lst_sort(t_list **begin_list, int (*cmp)())
{
	t_list	*a;
	t_list	*b;

	a = *begin_list;
	while (a != NULL)
	{
		b = *begin_list;
		while (b->next != NULL)
		{
			if ((*cmp)(b->content, b->next->content) > 0)
				ft_lst_swap(b);
			b = b->next;
		}
		a = a->next;
	}
}

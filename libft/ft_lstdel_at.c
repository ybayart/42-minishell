/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_at.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:06:51 by racohen           #+#    #+#             */
/*   Updated: 2019/11/29 17:09:58 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_at(t_list **list, int at, void (*del)(void *, size_t))
{
	t_list	*tmp;
	t_list	*prev;
	int		count;

	if (!list || !(*list))
		return ;
	tmp = *list;
	prev = NULL;
	count = 0;
	while (count != at && tmp->next != NULL)
	{
		prev = tmp;
		tmp = tmp->next;
		count++;
	}
	if (count == at)
	{
		if (prev)
			prev->next = tmp->next;
		else
			*list = tmp->next;
		del(tmp->content, tmp->content_size);
	}
}

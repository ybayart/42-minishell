/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_at.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:04:28 by racohen           #+#    #+#             */
/*   Updated: 2019/11/25 14:04:48 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_at(t_list **lst, t_list *new, int at)
{
	int		i;
	t_list	*tmp;

	i = 1;
	tmp = *lst;
	while (i <= (at - 1))
	{
		tmp = tmp->next;
		if (tmp == NULL)
			break ;
		i++;
	}
	if (tmp != NULL)
	{
		new->next = tmp->next;
		tmp->next = new;
	}
	else
	{
		ft_lstadd(lst, new);
	}
}

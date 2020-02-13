/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_at_typed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:04:28 by racohen           #+#    #+#             */
/*   Updated: 2020/02/13 21:50:11 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_lstadd_at_typed(t_typed **lst, t_typed *new, int at)
{
	int		i;
	t_typed	*tmp;

	i = 1;
	tmp = *lst;
	if (at == 0 && (new->next = *lst) == (*lst))
		*lst = new;
	else
	{
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
			ft_lstadd_typed(lst, new);
	}
}

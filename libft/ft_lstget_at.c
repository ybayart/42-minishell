/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget_at.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:07:39 by racohen           #+#    #+#             */
/*   Updated: 2019/11/25 14:07:54 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstget_at(t_list *lst, int at)
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

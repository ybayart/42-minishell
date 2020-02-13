/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_typed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 19:57:01 by racohen           #+#    #+#             */
/*   Updated: 2020/02/13 21:07:25 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_lstsize_typed(t_typed *lst)
{
	int		temp;
	t_typed	*elem;

	temp = 0;
	if (lst == NULL)
		return (temp);
	elem = lst;
	while (elem != NULL)
	{
		elem = elem->next;
		temp++;
	}
	return (temp);
}

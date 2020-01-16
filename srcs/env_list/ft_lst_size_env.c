/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_size_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 09:33:37 by racohen           #+#    #+#             */
/*   Updated: 2019/11/30 09:34:03 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_env.h"

int	ft_lst_size_env(t_list_env *lst)
{
	int			temp;
	t_list_env	*elem;

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

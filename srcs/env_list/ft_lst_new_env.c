/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_new_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:43:06 by racohen           #+#    #+#             */
/*   Updated: 2019/11/30 09:51:34 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_env.h"

t_list_env	*ft_lst_new_env(char *name, char *value)
{
	t_list_env	*elem;

	if ((elem = (t_list_env*)malloc(sizeof(t_list_env))) == NULL)
		return (NULL);
	elem->name = name;
	elem->value = value;
	elem->next = NULL;
	return (elem);
}

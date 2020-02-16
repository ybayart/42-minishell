/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_clear_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:39:17 by racohen           #+#    #+#             */
/*   Updated: 2020/02/16 16:37:29 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_lst_clear_env(t_list_env **lst)
{
	t_list_env	*tmp;
	t_list_env	*list;

	list = *lst;
	tmp = NULL;
	while (list != NULL)
	{
		if (list->next)
			tmp = list->next;
		else
			tmp = NULL;
		if (list->name != NULL)
			free(list->name);
		if (list->value != NULL)
			free(list->value);
		free(list);
		list = tmp;
	}
	*lst = NULL;
}

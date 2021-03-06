/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_del_at.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:46:55 by racohen           #+#    #+#             */
/*   Updated: 2020/01/16 15:20:21 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_lstdel_at_env(t_list_env **list, char *at)
{
	t_list_env	*tmp;
	t_list_env	*prev;

	if (!list || !(*list))
		return ;
	tmp = *list;
	prev = NULL;
	while (ft_strcmp(at, tmp->name) != 0 && tmp->next != NULL)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (ft_strcmp(at, tmp->name) == 0)
	{
		if (prev)
			prev->next = tmp->next;
		else
			*list = tmp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

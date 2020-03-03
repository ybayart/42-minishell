/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_sort_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 20:12:10 by racohen           #+#    #+#             */
/*   Updated: 2020/03/03 20:46:22 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_list_swap(t_list_env *list)
{
	char	*name;
	char	*value;

	name = list->name;
	value = list->value;
	list->name = list->next->name;
	list->value = list->next->value;
	list->next->name = name;
	list->next->value = value;
}

void	ft_list_sort_env(t_list_env **begin_list)
{
	char		*tmpa;
	char		*tmpb;
	t_list_env	*a;
	t_list_env	*b;

	a = *begin_list;
	while (a != NULL)
	{
		b = *begin_list;
		while (b->next != NULL)
		{
			tmpa = ft_strjoin_third(b->next->name, "=", b->next->value);
			tmpb = ft_strjoin_third(b->name, "=", b->value);
			if (ft_strcmp(tmpb, tmpa) > 0)
				ft_list_swap(b);
			free(tmpa);
			free(tmpb);
			b = b->next;
		}
		a = a->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_replace_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:53:38 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/26 12:44:03 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_lst_replace_env(t_list_env **list, char *name, char *value)
{
	t_list_env	*tmp;

	if (list && (*list))
	{
		tmp = *list;
		while (tmp->next)
		{
			if (ft_strncmp(tmp->name, name, ft_strlen(name)) == 0)
			{
				free(tmp->value);
				tmp->value = value;
			}
			tmp = tmp->next;
		}
	}
}

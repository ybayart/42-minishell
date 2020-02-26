/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:59:02 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/26 16:30:20 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	init_wildcard(t_list **sch, char ***args, int initpos, char *replace)
{
	if (((*sch) = ft_lstnew((*args)[initpos])) == NULL)
		return (0);
	if ((*args)[initpos][0] == '~' && !((*sch)->content = ft_strfrjoin(
ft_lst_find_env(&g_mini->env, "HOME"), (*sch)->content + 1, (*sch)->content)))
	{
		ft_lstclear(sch);
		return (0);
	}
	(*replace) = 0;
	if (ft_strncmp((*sch)->content, "/", 1) != 0 && ft_strncmp((*sch)->content,
					"./", 2) != 0 && ft_strncmp((*sch)->content, "../", 3) != 0)
		(*replace) = 1;
	return (1);
}

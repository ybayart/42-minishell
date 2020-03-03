/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:54:22 by racohen           #+#    #+#             */
/*   Updated: 2020/03/03 20:59:05 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	run_env(void)
{
	t_list_env	*list;

	list = g_mini->env;
	while (list)
	{
		write(1, list->name, ft_strlen(list->name));
		write(1, "=", 1);
		write(1, list->value, ft_strlen(list->value));
		write(1, "\n", 1);
		list = list->next;
	}
	return ;
}

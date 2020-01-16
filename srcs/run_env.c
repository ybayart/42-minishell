/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:54:22 by racohen           #+#    #+#             */
/*   Updated: 2019/12/04 17:13:42 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

void	run_env(const char *bin, char **argv, char **env)
{
	t_list_env	*list;

	(void)bin;
	(void)argv;
	(void)env;
	list = mini->env;
	while (list)
	{
		ft_printf("%s=%s\n", list->name, list->value);
		list = list->next;
	}	
	return ;
}

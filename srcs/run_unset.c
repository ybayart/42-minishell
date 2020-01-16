/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:54:51 by racohen           #+#    #+#             */
/*   Updated: 2020/01/16 12:52:44 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

void	run_unset(const char *bin, char **argv, char **env)
{
	int		i;

	(void)bin;
	(void)argv;
	(void)env;
	i = 0;
	while (argv[++i])
		ft_lstdel_at_env(&g_mini->env, argv[i]);
	return ;
}

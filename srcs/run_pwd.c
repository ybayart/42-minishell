/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:56:14 by racohen           #+#    #+#             */
/*   Updated: 2020/01/16 15:15:10 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	run_pwd(const char *bin, char **argv, char **env)
{
	char	*pwd;

	(void)bin;
	(void)argv;
	(void)env;
	pwd = ft_lst_find_env(&g_mini->env, PWD);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
}

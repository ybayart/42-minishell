/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 04:41:43 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/16 05:24:29 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		print_prompt(char clear)
{
	char	*pwd;

	if (clear == 1)
	{
		ft_lst_clear_typed(&(g_mini->typed));
		g_mini->typed_pos = 0;
	}
	g_mini->prompt_size = 0;
	if (g_mini->ispipe == 0)
	{
		pwd = ft_lst_find_env(&(g_mini->env), PWD);
		g_mini->prompt_size = write(1, pwd, ft_strlen(pwd));
	}
	g_mini->prompt_size += write(1, "> ", 2);
	g_mini->exec = 0;
}

void		sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_mini->signal = 1;
		signal(signo, SIG_IGN);
		signal(SIGINT, sig_handler);
		write(1, "\n", 1);
		print_prompt(1);
	}
	else if (signo == SIGQUIT && g_mini->exec == 1)
	{
		g_mini->signal = 1;
		signal(signo, SIG_IGN);
		signal(SIGQUIT, sig_handler);
		write(1, "Quit: 3\n", 8);
		print_prompt(1);
	}
}
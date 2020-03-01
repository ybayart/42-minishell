/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 04:41:43 by ybayart           #+#    #+#             */
/*   Updated: 2020/03/01 17:11:42 by yanyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		print_prompt(char clear)
{
	char	*pwd;
	char	*color;

	color = tgetstr("AF", NULL);
	tputs(tparm(color, COLOR_GREEN), 1, ft_termputs);
	if (clear == 1)
	{
		ft_lst_clear_typed(&(g_mini->tp));
		g_mini->tp_pos = 0;
	}
	g_mini->prompt_size = 0;
	if (g_mini->ispipe == 0)
	{
		pwd = ft_lst_find_env(&(g_mini->env), PWD);
		g_mini->prompt_size = write(1, pwd, ft_strlen(pwd));
	}
	g_mini->prompt_size += write(1, "> ", 2);
	g_mini->exec = 0;
	print_term("me", 0);
}

void		sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		kill(g_mini->fork, signo);
		g_mini->signal = 1;
		g_mini->ispipe = 0;
		signal(signo, SIG_IGN);
		signal(SIGINT, sig_handler);
		run_touch();
		write(1, "\n", 1);
		print_prompt(1);
	}
	else if (signo == SIGQUIT && g_mini->exec == 1)
	{
		g_mini->ispipe = 0;
		kill(g_mini->fork, signo);
		g_mini->signal = 1;
		signal(signo, SIG_IGN);
		signal(SIGQUIT, sig_handler);
		write(1, "Quit: 3\n", 8);
		print_prompt(1);
	}
}

void		endofprog(void)
{
	init_mode();
	ft_lst_clear_env(&(g_mini->env));
	ft_lst_clear_typed(&(g_mini->tp));
	free(g_mini->current);
	ft_lstclear(&(g_mini->history));
	free(g_mini);
}

void		check_empty_end(char ***args, size_t i)
{
	if ((*args)[i] != 0 && (*args)[i][0] == '\0')
	{
		free((*args)[i + 1]);
		free((*args)[i]);
		(*args)[i] = 0;
	}
}

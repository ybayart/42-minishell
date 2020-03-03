/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_termcaps_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:05:50 by yanyan            #+#    #+#             */
/*   Updated: 2020/03/03 17:49:26 by yanyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		ft_termcaps_update_pos(int oldpos)
{
	int		oldline;
	int		actline;

	oldline = (g_mini->prompt_size + oldpos) / tgetnum("co");
	actline = (g_mini->prompt_size + g_mini->tp_pos) / tgetnum("co");
	if (oldpos < g_mini->tp_pos && oldline != actline)
	{
		print_term_goto("DO", 0, 0, actline - oldline);
	}
	else if (oldpos > g_mini->tp_pos && oldline != actline)
	{
		print_term_goto("UP", 0, 0, oldline - actline);
	}
}

void		ft_termcaps_start(void)
{
	if (g_mini->prompt_size + g_mini->tp_pos > tgetnum("co"))
		print_term_goto("UP", 0, 0, (g_mini->prompt_size + g_mini->tp_pos)
									/ tgetnum("co"));
}

void		ft_termcaps_clean_all(void)
{
	if (ft_lstsize_typed(g_mini->tp) != g_mini->tp_pos)
	{
		ft_termcaps_start();
		print_term("cd", 0);
		g_mini->print_all = 2;
	}
}

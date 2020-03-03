/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_termcaps_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 20:38:10 by ybayart           #+#    #+#             */
/*   Updated: 2020/03/03 21:43:17 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_termcaps_printend_clean(char c)
{
	int		pos;
	int		size;

	pos = (g_mini->tp_pos < 1 ? 1 : g_mini->tp_pos);
	size = g_mini->prompt_size + pos;
	if (size % tgetnum("co") == 0 && c != 127 && g_mini->print_all == 0)
	{
		write(1, &c, 1);
		write(1, "\n", 1);
	}
	else if (size % (tgetnum("co") - 1) == 0 && c == 127)
	{
		print_term_goto("UP", 0, 0, 1);
		write(1, "\r", 1);
	}
	else
		write(1, "\r", 1);
	if (g_mini->print_all >= 0)
		print_term("ce", 0);
}

void	ft_termcaps_printend_aff(void)
{
	int		pos;
	int		size;
	int		start;

	pos = (g_mini->tp_pos < 1 ? 1 : g_mini->tp_pos);
	size = g_mini->prompt_size + pos;
	start = (size / tgetnum("co") * tgetnum("co") - g_mini->prompt_size);
	start = (start < 0 ? 0 : start);
	if (g_mini->print_all >= 1)
	{
		print_prompt(0);
		ft_lst_print_typed(g_mini->tp, -1);
	}
	else if (g_mini->print_all != -2)
	{
		if (size < tgetnum("co"))
		{
			print_prompt(0);
			ft_lst_print_typed(ft_lst_get_at_typed(g_mini->tp, start),
				tgetnum("co") - g_mini->prompt_size);
		}
		else
			ft_lst_print_typed(ft_lst_get_at_typed(g_mini->tp, start),
					tgetnum("co"));
	}
}

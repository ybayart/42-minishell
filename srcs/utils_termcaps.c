/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_termcaps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:54:12 by ybayart           #+#    #+#             */
/*   Updated: 2020/03/03 17:48:28 by yanyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	print_term(char *cap, char prompt)
{
	cap = tgetstr(cap, NULL);
	tputs(cap, 1, ft_termputs);
	if (prompt == 1)
		print_prompt(0);
}

void	print_term_goto(char *cap, char prompt, int x, int y)
{
	cap = tgetstr(cap, NULL);
	tputs(tgoto(cap, x, y), 1, ft_termputs);
	if (prompt == 1)
		print_prompt(0);
}

void	ft_termcaps_printend(char c, int *state)
{
	int		size;
	int		pos;
	int		start;

	pos = (g_mini->tp_pos < 1 ? 1 : g_mini->tp_pos);
	size = g_mini->prompt_size + pos;
	start = (size / tgetnum("co") * tgetnum("co") - g_mini->prompt_size);
	start = (start < 0 ? 0 : start);
	if ((*state) == 0)
	{
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
		size = g_mini->prompt_size + g_mini->tp_pos;
		if (ft_lstsize_typed(g_mini->tp) != g_mini->tp_pos)
		{
			if (g_mini->print_all == 2)
			{
				if ((g_mini->prompt_size + g_mini->tp_pos) / tgetnum("co")
	!= (g_mini->prompt_size + ft_lstsize_typed(g_mini->tp)) / tgetnum("co"))
					print_term_goto("UP", 0, 0, ((g_mini->prompt_size +
						ft_lstsize_typed(g_mini->tp)) / tgetnum("co")) -
					((g_mini->prompt_size + g_mini->tp_pos) / tgetnum("co")));
			}
			print_term_goto("ch", 0, 0, size - tgetnum("co") *
							(size / tgetnum("co")));
		}
	}
	else if ((*state) == 3 && c != 51 && c != 49)
		(*state) = 0;
}

void	ft_termcaps_change_value(char c, int *state)
{
	if (g_mini->history_pos < 0)
	{
		free(g_mini->current);
		g_mini->current = ft_lstconcat_typed(g_mini->tp);
	}
	ft_termcaps_printend(c, state);
}

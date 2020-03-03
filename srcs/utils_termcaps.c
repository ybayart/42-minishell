/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_termcaps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:54:12 by ybayart           #+#    #+#             */
/*   Updated: 2020/03/03 22:22:19 by ybayart          ###   ########.fr       */
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

	if ((*state) == 0)
	{
		ft_termcaps_printend_clean(c);
		ft_termcaps_printend_aff();
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
		}
		print_term_goto("ch", 0, 0, size - tgetnum("co") *
							(size / tgetnum("co")));
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

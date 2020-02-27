/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_termcaps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:54:12 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/27 16:26:45 by yanyan           ###   ########.fr       */
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
	if ((*state) == 0)
	{
		write(1, "\r", 1);
		print_prompt(0);
		ft_lst_print_typed(g_mini->tp);
		print_term_goto("ch", 0, 0, g_mini->prompt_size + g_mini->tp_pos);
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

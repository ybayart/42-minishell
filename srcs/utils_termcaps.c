/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_termcaps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:54:12 by ybayart           #+#    #+#             */
/*   Updated: 2020/03/02 16:26:29 by ybayart          ###   ########.fr       */
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

/*
**void	ft_termcaps_printend(char c, int *state)
**{
**	int		size;
**
**	size = g_mini->prompt_size + g_mini->tp_pos;
**	if ((*state) == 0)
**	{
**		if (size % tgetnum("co") == 0)
**			write(1, "\n", 1);
**		write(1, "\r", 1);
**		if (tgetnum("co") > size)
**			print_prompt(0);
**		if (tgetnum("co") <= size)
**		{
**			ft_lst_print_typed(ft_lst_get_at_typed(g_mini->tp, (tgetnum("co") * (size / tgetnum("co")) - 1) - g_mini->prompt_size));
**			print_term_goto("ch", 0, 0, size - (tgetnum("co") * (size / tgetnum("co"))) + 1);
**		}
**		else
**		{
**			ft_lst_print_typed(g_mini->tp);
**			print_term_goto("ch", 0, 0, size);
**		}
**	}
**	else if ((*state) == 3 && c != 51 && c != 49)
**		(*state) = 0;
**}
*/

/*
**void	ft_termcaps_printend(char c, int *state)
**{
**	int		size;
**
**	size = g_mini->prompt_size + ft_lstsize_typed(g_mini->tp);
**	if ((*state) == 0)
**	{
**		if (size % (tgetnum("co")) == 0 && c != 127)
**			write(1, "\n", 1);
**		print_term_goto("UP", 0, 0, (size / tgetnum("co") - 1));
**		print_term("cd", 0);
**		if (size % (tgetnum("co") - 1) == 0 && c == 127)
**			print_term_goto("UP", 0, 0, 1);
**		write(1, "\r", 1);
**		print_prompt(0);
**		ft_lst_print_typed(g_mini->tp);
**		size = g_mini->prompt_size + g_mini->tp_pos;
**		if (size % tgetnum("co") == 0)
**			print_term_goto("DO", 0, 0, size / tgetnum("co"));
**		print_term_goto("ch", 0, 0, size - tgetnum("co") * (size / (tgetnum("co"))));
**	}
**	else if ((*state) == 3 && c != 51 && c != 49)
**		(*state) = 0;
**}
*/

void	ft_termcaps_printend(char c, int *state)
{
	int		size;

	size = g_mini->prompt_size + (g_mini->tp_pos < 1 ? 1 : g_mini->tp_pos);
	if ((*state) == 0)
	{
		print_term_goto("ch", 0, 0, size - 1);
		print_term("cd", 0);
		ft_lst_print_typed(ft_lst_get_at_typed(g_mini->tp, g_mini->tp_pos));
		if (g_mini->tp_pos > 0)
			print_term_goto("ch", 0, 0, size);
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

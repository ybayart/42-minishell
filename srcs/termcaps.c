/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:45:48 by ybayart           #+#    #+#             */
/*   Updated: 2020/03/03 20:27:47 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_termcaps_arrow(char c, int *state)
{
	int		pos;

	(*state) = 0;
	if ((pos = g_mini->tp_pos) == g_mini->tp_pos && (c == 65 || c == 66))
	{
		ft_termcaps_start();
		print_term("cd", 0);
		set_history(c);
		g_mini->print_all = 1;
	}
	else if (c == 68 && g_mini->tp_pos > 0)
		g_mini->tp_pos--;
	else if (c == 67 && g_mini->tp_pos < ft_lstsize_typed(g_mini->tp))
		g_mini->tp_pos++;
	else if (c == 70 || c == 72)
		g_mini->tp_pos = (c == 70 ? ft_lstsize_typed(g_mini->tp) : 0);
	else
		(*state) = 3;
	if ((*state) == 0 && c != 65 && c != 66)
		ft_termcaps_update_pos(pos, -2);
}

static void	ft_termcaps_jump(char c, int *state)
{
	int		pos;

	if ((pos = g_mini->tp_pos) == g_mini->tp_pos && c == 68)
	{
		while (((*state) = 0) == 0 && g_mini->tp_pos > 0 &&
			ft_lst_get_at_typed(g_mini->tp, g_mini->tp_pos - 1)->c == ' ')
			g_mini->tp_pos--;
		while (g_mini->tp_pos > 0)
			if (ft_lst_get_at_typed(g_mini->tp, --g_mini->tp_pos)->c == ' ')
				break ;
		if (ft_lst_get_at_typed(g_mini->tp, g_mini->tp_pos)->c == ' ')
			g_mini->tp_pos++;
	}
	else if (((*state) = 0) == 0 && c == 67)
	{
		while (ft_lstsize_typed(g_mini->tp) - 1 > g_mini->tp_pos &&
			ft_lst_get_at_typed(g_mini->tp, g_mini->tp_pos)->c == ' ')
			g_mini->tp_pos++;
		while (ft_lstsize_typed(g_mini->tp) - 1 > g_mini->tp_pos)
			if (ft_lst_get_at_typed(g_mini->tp, ++g_mini->tp_pos)->c == ' ')
				break ;
		if (g_mini->tp_pos + 1 == ft_lstsize_typed(g_mini->tp))
			g_mini->tp_pos++;
	}
	ft_termcaps_update_pos(pos, -2);
}

static char	ft_termcaps_keys(char c, char key)
{
	if (key == 3)
	{
		if (c == 126)
		{
			ft_lstdel_at_typed(&(g_mini->tp), g_mini->tp_pos);
			ft_termcaps_clean_all();
		}
	}
	else if (c == 4)
	{
		write(1, "exit\n", 5);
		return (-1);
	}
	else if (c == 127 && g_mini->tp_pos > 0)
	{
		ft_lstdel_at_typed(&(g_mini->tp), --(g_mini->tp_pos));
		ft_termcaps_clean_all();
	}
	return (0);
}

char		ft_termcaps(char c)
{
	static int	state = 0;

	g_mini->print_all = 0;
	if ((c == 27 && state == 0) || (c == 91 && state == 1) ||
(c == 49 && state == 2) || (c == 59 && state == 3) || (c == 50 && state == 4))
		state++;
	else if (state == 2 || state == 5)
		state == 2 ? ft_termcaps_arrow(c, &state) : ft_termcaps_jump(c, &state);
	else if (state == 3 && (state = 0) == 0)
		ft_termcaps_keys(c, 3);
	else if (c == 4 && ft_lstsize_typed(g_mini->tp) == 0)
	{
		if (ft_termcaps_keys(c, 4) == -1)
			return (-1);
	}
	else if (c == 10 && ft_termcaps_do(c) == 1)
		return (1);
	else if (c == 127)
		ft_termcaps_keys(c, 4);
	else if (c != 4)
		ft_termcaps_do(c);
	ft_termcaps_change_value(c, &state);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:45:48 by ybayart           #+#    #+#             */
/*   Updated: 2020/03/01 22:31:03 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_termcaps_arrow(char c, int *state)
{
	(*state) = 0;
	if (c == 65 || c == 66)
	{
		set_history(c);
	}
	else if (c == 68 && g_mini->tp_pos > 0)
		g_mini->tp_pos--;
	else if (c == 67 && g_mini->tp_pos < ft_lstsize_typed(g_mini->tp))
		g_mini->tp_pos++;
	else if (c == 70 || c == 72)
		g_mini->tp_pos = (c == 70 ? ft_lstsize_typed(g_mini->tp) : 0);
	else
		(*state) = 3;
	if ((g_mini->prompt_size + g_mini->tp_pos) % tgetnum("co") == 0 && (c == 67 || c == 68))
		print_term_goto((c == 67 ? "DO" : "UP"), 0, 0, 1);
}

static void	ft_termcaps_jump(char c, int *state)
{
	char	jump;

	(*state) = 0;
	if ((jump = 0) == 0 && c == 68)
	{
		while (g_mini->tp_pos > 0 &&
			ft_lst_get_at_typed(g_mini->tp, g_mini->tp_pos - 1)->c == ' ')
			g_mini->tp_pos--;
		while (g_mini->tp_pos > 0)
			if (ft_lst_get_at_typed(g_mini->tp, --g_mini->tp_pos)->c == ' ')
				break ;
		if (ft_lst_get_at_typed(g_mini->tp, g_mini->tp_pos)->c == ' ')
			g_mini->tp_pos++;
	}
	else if (c == 67)
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
}

static char	ft_termcaps_keys(char c, char key)
{
	if (key == 3)
	{
		if (c == 126)
		{
			write(1, "\r", 1);
			print_term("ce", 0);
			ft_lstdel_at_typed(&(g_mini->tp), g_mini->tp_pos);
		}
	}
	else if (c == 4)
	{
		write(1, "exit\n", 5);
		return (-1);
	}
	else if (c == 127 && g_mini->tp_pos > 0)
	{
		write(1, "\r", 1);
		print_term("ce", 0);
		ft_lstdel_at_typed(&(g_mini->tp), --(g_mini->tp_pos));
	}
	return (0);
}

char		ft_termcaps(char c)
{
	static int	state = 0;

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
	else if (c == 10)
		return (1);
	else if (c == 12)
		print_term("cl", 0);
	else if (c == 127)
		ft_termcaps_keys(c, 4);
	else if (c != 4)
		ft_lstadd_at_typed(&(g_mini->tp), ft_lstnew_typed(c),
												(g_mini->tp_pos)++);
	ft_termcaps_change_value(c, &state);
	return (0);
}

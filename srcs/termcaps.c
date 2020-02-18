/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:45:48 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/18 15:25:55 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_termcaps_arrow(char c, int *state)
{
	(*state) = 0;
	if (c == 65 || c == 66)
	{
		set_history(c);
	}
	else if (c == 68 && g_mini->typed_pos > 0)
	{
		print_term("le", 0);
		g_mini->typed_pos--;
	}
	else if (c == 67 && g_mini->typed_pos < ft_lstsize_typed(g_mini->typed))
	{
		print_term("nd", 0);
		g_mini->typed_pos++;
	}
	else if (c == 70 || c == 72)
	{
		g_mini->typed_pos = (c == 70 ? ft_lstsize_typed(g_mini->typed) : 0);
		print_term_goto("ch", 0, 0, g_mini->prompt_size + g_mini->typed_pos);
	}
	else
		(*state) = 3;
}

char	ft_termcaps_keys(char c, char key)
{
	if (key == 3)
	{
		if (c == 126)
		{
			write(1, "\r", 1);
			print_term("ce", 0);
			ft_lstdel_at_typed(&(g_mini->typed), g_mini->typed_pos);
		}
	}
	else if (c == 4)
	{
		write(1, "exit\n", 5);
		return (-1);
	}
	else if (c == 127 && g_mini->typed_pos > 0)
	{
		write(1, "\r", 1);
		print_term("ce", 0);
		ft_lstdel_at_typed(&(g_mini->typed), --(g_mini->typed_pos));
	}
	return (0);
}

void	ft_termcaps_printend(char c, int *state)
{
	if ((*state) == 0)
	{
		write(1, "\r", 1);
		print_prompt(0);
		ft_lst_print_typed(g_mini->typed);
		print_term_goto("ch", 0, 0, g_mini->prompt_size + g_mini->typed_pos);
	}
	else if ((*state) == 3 && c != 51)
		(*state) = 0;
}

void	change_value(void)
{
	if (g_mini->history_pos < 0)
		g_mini->current = ft_lstconcat_typed(g_mini->typed);
}

char	ft_termcaps(char c)
{
	static int	state = 0;

	if ((c == 27 && state == 0) || (c == 91 && state == 1))
		state++;
	else if (state == 2)
		ft_termcaps_arrow(c, &state);
	else if (state == 3 && (state = 0) == 0)
		ft_termcaps_keys(c, 3);
	else if (c == 4 && ft_lstsize_typed(g_mini->typed) == 0)
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
		ft_lstadd_at_typed(&(g_mini->typed), ft_lstnew_typed(c),
												(g_mini->typed_pos)++);
	change_value();
	ft_termcaps_printend(c, &state);
	return (0);
}

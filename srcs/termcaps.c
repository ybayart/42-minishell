/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:45:48 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/14 00:20:38 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	ft_termcaps(char c)
{
	static int	state = 0;
	char		*cap;

	if ((c == 27 && state == 0) || (c == 91 && state == 1))
		state++;
	else if (state == 2)
	{
		if (c == 68)
		{
			if (g_mini->typed_pos > 0)
			{
				cap = tgetstr("le", NULL);
				tputs(cap, 1, putchar);
				fflush(stdout);
				g_mini->typed_pos--;
			}
		}
		else if (c == 67)
		{
			if (g_mini->typed_pos < ft_lstsize_typed(g_mini->typed))
			{
				cap = tgetstr("nd", NULL);
				tputs(cap, 1, putchar);
				fflush(stdout);
				g_mini->typed_pos++;
			}
		}
		state++;
	}
	else if (state == 3)
	{
		if (c == 126)
		{
			write(1, "\r", 1);
			cap = tgetstr("ce", NULL);
			tputs(cap, 1, putchar);
			fflush(stdout);
			ft_lstdel_at_typed(&(g_mini->typed), g_mini->typed_pos);
		}
		state = 0;
	}
	else if (c == 4 && ft_lstsize_typed(g_mini->typed) == 0)
	{
		write(1, "exit\n", 5);
		return (-1);
	}
	else if (c == 10)
		return (1);
	else if (c == 12)
	{
		cap = tgetstr("cl", NULL);
		tputs(cap, 1, putchar);
		fflush(stdout);
	}
	else if (c == 127)
	{
		if (g_mini->typed_pos > 0)
		{
			write(1, "\r", 1);
			cap = tgetstr("ce", NULL);
			tputs(cap, 1, putchar);
			fflush(stdout);
			ft_lstdel_at_typed(&(g_mini->typed), --(g_mini->typed_pos));
		}
	}
	else if (c != 4)
		ft_lstadd_at_typed(&(g_mini->typed), ft_lstnew_typed(c), (g_mini->typed_pos)++);
	if (state == 0)
	{
		write(1, "\r", 1);
		print_prompt(g_mini->env);
		ft_lst_print_typed(g_mini->typed);
		cap = tgetstr("ch", NULL);
		tputs(tgoto(cap, 0, g_mini->prompt_size + g_mini->typed_pos), 1, putchar);
		fflush(stdout);
	}
	else if (state == 3 && c != 51)
		state = 0;
	return (0);
}

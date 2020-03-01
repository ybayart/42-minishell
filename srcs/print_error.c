/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 23:53:18 by ybayart           #+#    #+#             */
/*   Updated: 2020/03/01 17:35:11 by yanyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/*
**	1: "minishell: bin: str"
**	2: "minishell: bin: str: strerror(errno)"
**	3: "minishell: str: strerror(errno)"
**	4: "minishell: bin: str: comp"
**	5: "minishell: str `comp'"
*/

static void	print_error_init(char state, char *bin)
{
	write(2, "minishell", 9);
	if (state == 1 || state == 2 || state == 4)
	{
		write(2, ": ", 2);
		write(2, bin, ft_strlen(bin));
	}
}

static void	print_error_message(char state, char *str, char *comp)
{
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	if (state == 2 || state == 3)
	{
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
	}
	else if (state == 4 || state == 5)
	{
		write(2, (state == 4 ? ": " : " `"), 2);
		if (state == 5 && (comp == 0 || comp[0] == '\0'))
			write(2, "newline", 7);
		else
			write(2, comp, ft_strlen(comp));
		if (state == 5)
			write(2, "'", 1);
	}
	write(2, "\n", 1);
}

void		print_error(int state, char *str, char *bin, char *comp)
{
	tputs(tparm(tgetstr("AF", NULL), COLOR_RED), 1, ft_termputs);
	print_error_init(state, bin);
	print_error_message(state, str, comp);
	g_mini->last_exit = 1;
	print_term("me", 0);
}

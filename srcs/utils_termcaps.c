/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_termcaps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:54:12 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/15 20:08:54 by ybayart          ###   ########.fr       */
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

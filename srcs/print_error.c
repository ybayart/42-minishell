/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 23:53:18 by ybayart           #+#    #+#             */
/*   Updated: 2020/01/21 19:27:57 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/*
**	1: "minishell: str: command not found"
**	2: "minishell: bin: str: strerror(errno)"
**	3: "minishell: str: strerror(errno)"
**	4: "minishell: bin: str: comp"
*/

void	print_error(int state, char *str, char *bin, char *comp)
{
	write(2, "minishell: ", 11);
	if (state == 1)
	{
		write(2, str, ft_strlen(str));
		write(2, ": ", 2);
		write(2, "command not found", 17);
	}
	else if (state == 2 || state == 4)
	{
		write(2, bin, ft_strlen(bin));
		write(2, ": ", 2);
		write(2, str, ft_strlen(str));
		write(2, ": ", 2);
		if (state == 2)
			write(2, strerror(errno), ft_strlen(strerror(errno)));
		else
			write(2, comp, ft_strlen(comp));
	}
	else if (state == 3)
	{
		write(2, str, ft_strlen(str));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
	}
	write(2, "\n", 1);
	g_mini->last_exit = 1;
}

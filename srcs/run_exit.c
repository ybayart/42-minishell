/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:55:43 by racohen           #+#    #+#             */
/*   Updated: 2020/02/25 09:09:11 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	run_exit(char **argv)
{
	write(1, "exit\n", 5);
	if (argv[1] != 0)
	{
		if (ft_isstrint(argv[1]) == 0)
		{
			print_error(4, argv[1], "exit", "numeric argument required");
			init_mode();
			exit(255);
		}
		else if (argv[2] != 0)
			print_error(1, "too many argument", "exit", NULL);
		else
		{
			init_mode();
			exit(ft_atoi(argv[1]));
		}
	}
	else
	{
		init_mode();
		exit(0);
	}
}

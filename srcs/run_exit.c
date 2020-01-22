/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:55:43 by racohen           #+#    #+#             */
/*   Updated: 2020/01/22 17:16:28 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	run_exit(const char *bin, char **argv, char **env)
{
	write(1, "exit\n", 5);
	if (argv[1] != 0)
	{
		if (ft_isstrint(argv[1]) == 0)
		{
			print_error(4, argv[1], "exit", "numeric argument required");
			exit(255);
		}
		else if (argv[2] != 0)
		{
			print_error(1, "too many argument", "exit", NULL);
		}
	}
	else
		exit(0);
	(void)bin;
	(void)env;
}

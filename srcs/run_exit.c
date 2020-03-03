/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:55:43 by racohen           #+#    #+#             */
/*   Updated: 2020/03/04 00:12:37 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	localend(char **argv, char *cmd)
{
	ft_free_tab((void**)argv);
	free(cmd);
	endofprog();
}

void		run_exit(char **argv, char *cmd)
{
	int		tmp;

	write(1, "exit\n", 5);
	if (argv[1] != 0)
	{
		if (ft_isstrint(argv[1]) == 0)
		{
			print_error(4, argv[1], "exit", "numeric argument required");
			localend(argv, cmd);
			exit(255);
		}
		else if (argv[2] != 0)
			print_error(1, "too many argument", "exit", NULL);
		else
		{
			tmp = ft_atoi(argv[1]);
			localend(argv, cmd);
			exit(tmp);
		}
	}
	else
	{
		localend(argv, cmd);
		exit(0);
	}
}

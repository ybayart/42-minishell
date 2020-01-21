/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:55:43 by racohen           #+#    #+#             */
/*   Updated: 2020/01/21 19:28:50 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	run_exit(const char *bin, char **argv, char **env)
{
	int		i;

	if (argv[1] != 0 && ft_isstrint(argv[1]) == 0)
	{
		print_error(4, argv[1], "exit", "numeric argument required");
	}
	printf("bin: %s\n", bin);
	printf("argv:\n");
	i = -1;
	while (argv[++i] != 0)
		printf("argv[%d]: %s\n", i, argv[i]);
	printf("env:\n");
	i = -1;
	while (env[++i] != 0)
		printf("env[%d]: %s\n", i, env[i]);
}

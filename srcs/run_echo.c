/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:54:07 by racohen           #+#    #+#             */
/*   Updated: 2020/02/10 13:20:56 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	run_echo(const char *bin, char **argv, char **env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (argv[j + 1] != 0)
		while (strcmp(argv[j + 1], "-n") == 0)
			j++;
	while (argv[++i + j] != 0)
	{
		if (i != 1)
			write(1, " ", 1);
		write(1, argv[i + j], ft_strlen(argv[i + 1]));
	}
	if (j == 0)
		write(1, "\n", 1);
	(void)bin;
	(void)env;
}

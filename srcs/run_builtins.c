/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:55:56 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/18 15:24:30 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	run_builtins(char *cmd, char **argv)
{
	if (ft_strcmp(cmd, "cd") == 0)
		run_cd(argv);
	else if (ft_strcmp(cmd, "echo") == 0)
		run_echo(argv);
	else if (ft_strcmp(cmd, "pwd") == 0)
		run_pwd();
	else if (ft_strcmp(cmd, "export") == 0)
		run_export(argv);
	else if (ft_strcmp(cmd, "unset") == 0)
		run_unset(argv);
	else if (ft_strcmp(cmd, "env") == 0)
		run_env();
	else if (ft_strcmp(cmd, "exit") == 0)
	{
		free(cmd);
		run_exit(argv);
	}
	else
		return (0);
	return (1);
}

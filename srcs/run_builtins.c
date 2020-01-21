/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:55:56 by ybayart           #+#    #+#             */
/*   Updated: 2020/01/21 18:43:01 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		run_builtins(char *cmd, const char *bin, char **argv, char **env)
{
	if (ft_strcmp(cmd, "cd") == 0)
		run_cd(bin, argv, env);
	else if (ft_strcmp(cmd, "echo") == 0)
		run_echo(bin, argv, env);
	else if (ft_strcmp(cmd, "pwd") == 0)
		run_pwd(bin, argv, env);
	else if (ft_strcmp(cmd, "export") == 0)
		run_export(bin, argv, env);
	else if (ft_strcmp(cmd, "unset") == 0)
		run_unset(bin, argv, env);
	else if (ft_strcmp(cmd, "env") == 0)
		run_env(bin, argv, env);
	else if (ft_strcmp(cmd, "exit") == 0)
		run_exit(bin, argv, env);
	else
		return (0);
	return (1);
}

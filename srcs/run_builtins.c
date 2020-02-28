/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:55:56 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/28 16:16:07 by yanyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	run_forked(char *cmd, char **argv)
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
}

int			run_builtins(char *cmd, char **argv)
{
	pid_t	id;

	if (ft_strcmp(cmd, "exit") == 0)
	{
		free(cmd);
		run_exit(argv);
	}
	if ((id = fork()) == 0)
	{
		run_forked(cmd, argv);
		exit(0);
	}
	g_mini->exec++;
	g_mini->fork = id;
	if (g_mini->redir == 0)
	{
		waitpid(id, &g_mini->last_exit, 0);
		g_mini->last_exit = WEXITSTATUS(g_mini->last_exit);
		g_mini->exec--;
	}
	return (1);
}

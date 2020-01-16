/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:55:56 by ybayart           #+#    #+#             */
/*   Updated: 2020/01/16 15:14:07 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		run_builtins(char *cmd, const char *bin, char **argv, char **env)
{
	size_t		len;

	len = ft_strlen(cmd);
	if (ft_strncmp(cmd, "cd", len) == 0)
		run_cd(bin, argv, env);
	else if (ft_strncmp(cmd, "echo", len) == 0)
		run_echo(bin, argv, env);
	else if (ft_strncmp(cmd, "pwd", len) == 0)
		run_pwd(bin, argv, env);
	else if (ft_strncmp(cmd, "export", len) == 0)
		run_export(bin, argv, env);
	else if (ft_strncmp(cmd, "unset", len) == 0)
		run_unset(bin, argv, env);
	else if (ft_strncmp(cmd, "env", len) == 0)
		run_env(bin, argv, env);
	else
		return (0);
	return (1);
}

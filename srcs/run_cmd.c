/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:53:44 by racohen           #+#    #+#             */
/*   Updated: 2020/02/18 14:26:58 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		is_convert_red(char *str)
{
	if (*str == '|' || *str == '<' || *str == '>' ||
		strncmp("<<", str, 3) == 0 || strncmp(">>", str, 3) == 0)
		return (1);
	return (0);
}

int		ft_get_len(char **str)
{
	int i;

	i = -1;
	while (str[++i])
		if (is_convert_red(str[i]))
			return (i);
	return (i);
}

void	shell_ex(const char *bin, char **argv, char **env)
{
	pid_t	id;

	if ((id = fork()) == 0)
		execve(bin, argv, env);
	else
	{
		waitpid(id, &g_mini->last_exit, 0);
		g_mini->last_exit = WEXITSTATUS(g_mini->last_exit);
	}
}

int		check_builtins(char *tmp)
{
	if (!ft_strcmp(tmp, "cd") || !ft_strcmp(tmp, "echo") ||
		!ft_strcmp(tmp, "pwd") || !ft_strcmp(tmp, "export") ||
		!ft_strcmp(tmp, "unset") || !ft_strcmp(tmp, "env") ||
		!ft_strcmp(tmp, "exit"))
		return (1);
	return (0);
}

void	run_cmd(const char *bin, char **argv, char **env)
{
	int		len;
	char	**tmp;

	if (check_builtins((char*)bin))
	{
		len = 0;
		tmp = malloc(sizeof(char*) * 2);
		tmp[1] = 0;
		tmp[0] = (char*)bin;
	}
	else
	{
		tmp = ft_split(bin, '/');
		len = ft_get_len(tmp) - 1;
	}
	if (run_builtins(tmp[len], argv) == 0)
		shell_ex(bin, argv, env);
}

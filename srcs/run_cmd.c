/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:53:44 by racohen           #+#    #+#             */
/*   Updated: 2020/01/16 11:55:50 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

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
	int		status;


	status = 0;
	if ((id = fork()) == 0)
		execve(bin, argv, env);
	else
		waitpid(id, &status, 0);
	if (status == 256)
		mini->last_exit = 1;
	else
		mini->last_exit = 0;
}

int		check_builtins(char *tmp)
{
	if (!ft_strcmp(tmp, "cd") || !ft_strcmp(tmp, "echo") || !ft_strcmp(tmp, "pwd") ||
		!ft_strcmp(tmp, "export") || !ft_strcmp(tmp, "unset") || !ft_strcmp(tmp, "env"))
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
		*tmp = (char*)bin;
	}
	else
	{
		tmp = ft_split(bin, '/');
		len = ft_get_len(tmp) - 1;
	}
	if (ft_strncmp(tmp[len], "cd", ft_strlen(tmp[len])) == 0)
		run_cd(bin, argv, env);
	else if (ft_strncmp(tmp[len], "echo", ft_strlen(tmp[len])) == 0)
		run_echo(bin, argv, env);
	else if (ft_strncmp(tmp[len], "pwd", ft_strlen(tmp[len])) == 0)
		run_pwd(bin, argv, env);
	else if (ft_strncmp(tmp[len], "export", ft_strlen(tmp[len])) == 0)
		run_export(bin, argv, env);
	else if (ft_strncmp(tmp[len], "unset", ft_strlen(tmp[len])) == 0)
		run_unset(bin, argv, env);
	else if (ft_strncmp(tmp[len], "env", ft_strlen(tmp[len])) == 0)
		run_env(bin, argv, env);
	else
		shell_ex(bin, argv, env);
	ft_free_tab((void**)tmp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 15:49:11 by racohen           #+#    #+#             */
/*   Updated: 2020/01/23 21:08:04 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	print_prompt(t_list_env *list)
{
	ft_printf("%s> ", ft_lst_find_env(&list, PWD));
}

void		sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_mini->signal = 1;
		signal(signo, SIG_IGN);
		signal(SIGINT, sig_handler);
		write(1, "\n", 1);
		print_prompt(g_mini->env);
	}
}

static void	setfd(int f_in, int f_out, char state)
{
	static int	fd[2];

	if (state == 0)
	{
		if (f_out != 1)
			fd[0] = dup(1);
		if (f_out != 1)
			dup2(f_out, 1);
		if (f_in != 0)
			fd[1] = dup(0);
		if (f_in != 0)
			dup2(f_in, 0);
	}
	else if (state == 1)
	{
		if (f_out != 1)
			dup2(fd[0], 1);
		if (f_out != 1)
			close(f_out);
		if (f_in != 0)
			dup2(fd[1], 0);
		if (f_in != 0)
			close(f_in);
	}
}

void		space_cmd(char **cmd, int f_in, int f_out)
{
	char	*path;
	char	**res;
	size_t	i;

	i = ft_tablen((const char**)cmd);
	setfd(f_in, f_out, 0);
	if (check_builtins(cmd[0]))
		path = ft_strdup(cmd[0]);
	else if ((path = search_bin((char*)cmd[0],
			ft_lst_find_env(&g_mini->env, PATH))) == NULL)
		return (print_error(1, "command not found", cmd[0], NULL));
	if (ft_strcmp(cmd[0], "export") != 0)
		cmd = replace_quote_path(cmd);
	if ((res = (char**)malloc(sizeof(char*) * (i + 1))) == NULL)
		return ;
	res[i] = 0;
	i = -1;
	while (cmd[++i])
		res[i] = cmd[i];
	run_cmd(path, res, ft_list_to_tab_env(g_mini->env));
	free(res);
	setfd(f_in, f_out, 1);
}

int			shell(void)
{
	char	*line;

	if ((line = ft_strdup("")) == NULL)
		return (EXIT_FAILURE);
	signal(SIGINT, sig_handler);
	while (g_mini->alive)
	{
		if (g_mini->signal == 0)
			print_prompt(g_mini->env);
		else
			g_mini->signal = 0;
		if ((get_next_line(0, &line)) <= 0)
		{
			write(1, "exit\n", 5);
			exit(EXIT_FAILURE);
		}
		g_mini->signal = 0;
		if (ft_strreplace(&line, "$?", ft_itoa(g_mini->last_exit)) == NULL)
			return (EXIT_FAILURE);
		getargs_cmd(ft_strtrim(line, " "));
		free(line);
	}
	return (EXIT_SUCCESS);
}

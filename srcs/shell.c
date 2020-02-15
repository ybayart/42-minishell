/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 15:49:11 by racohen           #+#    #+#             */
/*   Updated: 2020/02/15 21:25:47 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		print_prompt(char clear)
{
	if (clear == 1)
	{
		ft_lst_clear_typed(&(g_mini->typed));
		g_mini->typed_pos = 0;
	}
	g_mini->prompt_size = 0;
	if (g_mini->ispipe == 0)
		g_mini->prompt_size = ft_printf("%s",
				ft_lst_find_env(&(g_mini->env), PWD));
	write(1, "> ", 2);
	g_mini->prompt_size += 2;
}

void		sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_mini->signal = 1;
		signal(signo, SIG_IGN);
		signal(SIGINT, sig_handler);
		write(1, "\n", 1);
		print_prompt(1);
	}
	else if (signo == SIGQUIT && ft_lstsize_typed(g_mini->typed) == 0)
	{
		g_mini->signal = 1;
		signal(signo, SIG_IGN);
		signal(SIGQUIT, sig_handler);
		write(1, "Quit: 3\n", 8);
		print_prompt(1);
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
	if ((res = (char**)malloc(sizeof(char*) * (i + 1))) == NULL)
		return ;
	res[i] = 0;
	i = -1;
	while (cmd[++i])
		res[i] = cmd[i];
	res = replace_quote_path(res);
	run_cmd(path, res, ft_list_to_tab_env(g_mini->env));
	free(res);
	setfd(f_in, f_out, 1);
}

int			shell(void)
{
	char	ret;
	char	c;
	char	*line;

	print_prompt(0);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	line = ft_strdup("");
	while (read(0, &c, 1) == 1)
		if ((ret = ft_termcaps(c)) == -1)
			return (EXIT_FAILURE);
		else if (ret == 1)
		{
			if (!(line = ft_strfdjoin(line, ft_lstconcat_typed(g_mini->typed))))
				return (EXIT_FAILURE);
			if (ft_strreplace(&line, "$?", ft_itoa(g_mini->last_exit)) == NULL)
				return (EXIT_FAILURE);
			write(1, "\n", 1);
			if (ft_strlen((line = ft_strtrim(line, " \t\n\v\f\r"))) != 0)
			{
				if (line[ft_strlen(line) - 1] == '|' && (g_mini->ispipe = 1))
				{
					print_prompt(1);
					continue ;
				}
				else if ((g_mini->ispipe = 0) == 0)
				{
					add_history(line);
					getargs_cmd(line);
				}
			}
			free(line);
			line = ft_strdup("");
			print_prompt(1);
		}
	return (EXIT_SUCCESS);
}

/*
**int			shell(void)
**{
**	char	*line;
**
**	if ((line = ft_strdup("")) == NULL)
**		return (EXIT_FAILURE);
**	signal(SIGINT, sig_handler);
**	signal(SIGQUIT, sig_handler);
**	while (g_mini->alive)
**	{
**		if (g_mini->signal == 0)
**			print_prompt(g_mini->env);
**		else
**			g_mini->signal = 0;
**		if ((get_next_line(0, &line)) <= 0)
**		{
**			write(1, "exit\n", 5);
**			exit(EXIT_FAILURE);
**		}
**		g_mini->signal = 0;
**		if (ft_strreplace(&line, "$?", ft_itoa(g_mini->last_exit)) == NULL)
**			return (EXIT_FAILURE);
**		if (ft_strlen((line = ft_strtrim(line, " \t\n\v\f\r"))) != 0)
**			getargs_cmd(line);
**		free(line);
**	}
**	return (EXIT_SUCCESS);
**}
*/

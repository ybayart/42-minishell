/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 15:49:11 by racohen           #+#    #+#             */
/*   Updated: 2020/02/13 23:04:28 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	print_prompt(t_list_env *list)
{
	g_mini->prompt_size = ft_printf("%s> ", ft_lst_find_env(&list, PWD));
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
	else if (signo == SIGQUIT)
	{
		g_mini->signal = 1;
		signal(signo, SIG_IGN);
		signal(SIGQUIT, sig_handler);
		write(1, "Quit: 3\n", 8);
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
	char	c;
	int		state;
	char	*cap;
	char	*line;

	print_prompt(g_mini->env);
	state = 0;
	while (read(0, &c, 1) == 1)
	{
		if ((c == 27 && state == 0) || (c == 91 && state == 1))
			state++;
		else if (state == 2)
		{
			if (c == 68)
			{
				if (g_mini->typed_pos > 0)
				{
					cap = tgetstr("le", NULL);
					tputs(cap, 1, putchar);
					fflush(stdout);
					g_mini->typed_pos--;
				}
			}
			else if (c == 67)
			{
				if (g_mini->typed_pos < ft_lstsize_typed(g_mini->typed))
				{
					cap = tgetstr("nd", NULL);
					tputs(cap, 1, putchar);
					fflush(stdout);
					g_mini->typed_pos++;
				}
			}
			state++;
		}
		else if (state == 3)
		{
			if (c == 126)
			{
				write(1, "\r", 1);
				cap = tgetstr("ce", NULL);
				tputs(cap, 1, putchar);
				fflush(stdout);
				ft_lstdel_at_typed(&(g_mini->typed), g_mini->typed_pos);
			}
			state = 0;
		}
		else if (c == 10)
		{
			if ((line = ft_lstconcat_typed(g_mini->typed)) == NULL)
				return (EXIT_FAILURE);
			if (ft_strreplace(&line, "$?", ft_itoa(g_mini->last_exit)) == NULL)
				return (EXIT_FAILURE);
			write(1, "\n", 1);
			if (ft_strlen((line = ft_strtrim(line, " \t\n\v\f\r"))) != 0)
				getargs_cmd(line);
			ft_lst_clear_typed(&(g_mini->typed));
			g_mini->typed_pos = 0;
		}
		else if (c == 12)
		{
			cap = tgetstr("cl", NULL);
			tputs(cap, 1, putchar);
			fflush(stdout);
		}
		else if (c == 127)
		{
			if (g_mini->typed_pos > 0)
			{
				write(1, "\r", 1);
				cap = tgetstr("ce", NULL);
				tputs(cap, 1, putchar);
				fflush(stdout);
				ft_lstdel_at_typed(&(g_mini->typed), --(g_mini->typed_pos));
			}
		}
		else
			ft_lstadd_at_typed(&(g_mini->typed), ft_lstnew_typed(c), (g_mini->typed_pos)++);
		if (state == 0)
		{
			write(1, "\r", 1);
			print_prompt(g_mini->env);
			ft_lst_print_typed(g_mini->typed);
			cap = tgetstr("ch", NULL);
			tputs(tgoto(cap, 0, g_mini->prompt_size + g_mini->typed_pos), 1, putchar);
			fflush(stdout);
		}
		else if (state == 3 && c != 51)
			state = 0;
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

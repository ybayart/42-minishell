/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 15:49:11 by racohen           #+#    #+#             */
/*   Updated: 2020/02/27 12:15:53 by yanyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		space_cmd(char ***cmd, int f_in, int f_out)
{
	char	*path;
	size_t	i;

	i = ft_tablen((const char**)(*cmd));
	setfd(f_in, f_out, 0);
	if (check_builtins((*cmd)[0]))
		path = ft_strdup((*cmd)[0]);
	else if ((path = search_bin((char*)(*cmd)[0],
			ft_lst_find_env(&g_mini->env, PATH))) == NULL)
	{
		print_error(1, "command not found", (*cmd)[0], NULL);
		return (ft_free_tab((void**)(*cmd)));
	}
	utils_space_cmd(cmd, i, path);
	setfd(f_in, f_out, 1);
}

static char	shell_do(char **line)
{
	char	*tmp;

	write(1, "\n", 1);
	tmp = (*line);
	if (ft_strlen(((*line) = ft_strtrim((*line), " \t\n\v\f\r"))) != 0)
	{
		free(tmp);
		if ((*line)[ft_strlen((*line)) - 1] == '|' && (g_mini->ispipe = 1))
		{
			print_prompt(1);
			return (0);
		}
		else if ((g_mini->ispipe = 0) == 0)
			utils_shell_do(line);
	}
	return (1);
}

int			shell(void)
{
	char	ret;
	char	c;
	char	*line;

	line = NULL;
	while (read(0, &c, 1) == 1)
		if ((ret = ft_termcaps(c)) == -1)
			return (EXIT_FAILURE);
		else if (ret == 1)
		{
			utils_shell(&line);
			if (!(line = ft_strfdjoin(line, ft_lstconcat_typed(g_mini->typed)))
		|| !ft_strreplace(&line, ft_strdup("$?"), ft_itoa(g_mini->last_exit)))
				return (EXIT_FAILURE);
			if (shell_do(&line) == 0)
				continue ;
			free(line);
			line = NULL;
			if (g_mini->signal == 0)
				print_prompt(1);
			g_mini->signal = 0;
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

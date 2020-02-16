/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutargs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 23:02:56 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/16 18:37:23 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/*
**	0: O_RDONLY
**	2: O_RDWR
**	10: O_RDWR | O_APPEND
**	962: O_RDWR | O_CREAT | S_IRWXU
**	970: O_RDWR | O_CREAT | O_APPEND | S_IRWXU
*/

#define MSGERROR "syntax error near unexpected token"

static char	init(t_cutargs *data, char **ar, char state)
{
	if (state == 0)
	{
		(*data).i = -1;
		(*data).len = 1;
		while (ar[++(*data).i] != 0)
			if (ft_strcmp(ar[(*data).i], "|") == 0)
				(*data).len++;
		(*data).i = -1;
		(*data).j = -1;
		(*data).isredir = 0;
	}
	(*data).cmd = NULL;
	if (((*data).cmd = ft_addstr((*data).cmd)) == NULL)
		return (0);
	(*data).f_in = 0;
	(*data).f_out = 1;
	return (1);
}

static char	launch_cmd(t_cutargs *data, char **ar, char state)
{
	if ((*data).cmd[ft_tablen((const char**)(*data).cmd) - 1][0] == '\0')
		(*data).cmd[ft_tablen((const char**)(*data).cmd) - 1] = 0;
	if (state == 0)
	{
		(*data).j++;
		pipe((*data).fd[(*data).j % 2]);
		make_redir(0, (*data).j, (*data).len, (*data).fd);
		if ((*data).f_out != 1)
			run_touch();
		else
			space_cmd((*data).cmd, (*data).f_in, (*data).f_out);
		make_redir(1, (*data).j, (*data).len, (*data).fd);
		if ((*data).f_out != 1)
			space_cmd((*data).cmd, (*data).f_in, (*data).f_out);
		(*data).isredir = 1;
	}
	else
		space_cmd((*data).cmd, (*data).f_in, (*data).f_out);
	if (init(data, ar, 1) == 0)
		return (0);
	return (1);
}

static void	endcuts(t_cutargs data)
{
	if (data.cmd[ft_tablen((const char**)data.cmd) - 1][0] == '\0')
		data.cmd[ft_tablen((const char**)data.cmd) - 1] = 0;
	if (data.isredir == 1)
	{
		data.j++;
		pipe(data.fd[data.j % 2]);
		make_redir(0, data.j, data.len, data.fd);
	}
	space_cmd(data.cmd, data.f_in, data.f_out);
	if (data.isredir == 1)
	{
		make_redir(1, data.j, data.len, data.fd);
		data.isredir = 0;
	}
}

static int	do_if(t_cutargs *data, char **ar, char state)
{
	if (state == 0 && istoken(ar[(*data).i]) && istoken(ar[(*data).i + 1]) &&
			(ar[(*data).i][0] != '>' || ar[(*data).i + 1][0] != '>' ||
			(istoken(ar[(*data).i + 2]) && (*data).i++)))
		return (0);
	else if (state == 1 && ((*data).state = 0) == 0 &&
			ft_strcmp(ar[(*data).i], "<") == 0 && (*data).state++ == 0 &&
			openfile(&(*data).f_in, ar[++(*data).i], 0, 0) == 0)
		return (0);
	else if (state == 2 && ft_strcmp(ar[(*data).i], ">") == 0 &&
		ar[(*data).i + 1] != 0 && ft_strcmp(ar[(*data).i + 1], ">") == 0 &&
		(*data).state++ == 0 && ++(*data).i != 0 &&
		openfile(&(*data).f_out, ar[++(*data).i], 1, 970) == 0)
		return (0);
	else if (state == 3 && ft_strcmp(ar[(*data).i], ">") == 0 &&
(*data).state++ == 0 && openfile(&(*data).f_out, ar[++(*data).i], 1, 962) == 0)
		return (0);
	else if (state == 4 && ft_strcmp(ar[(*data).i], "|") == 0 &&
		(*data).state++ == 0 && launch_cmd(data, ar, 0) == 0)
		return (0);
	else if (state == 5 && ft_strcmp(ar[(*data).i], ";") == 0 &&
		(*data).state++ == 0 && launch_cmd(data, ar, 1) == 0)
		return (0);
	return (1);
}

void		cutargs(char **ar)
{
	t_cutargs	data;

	if ((ar = ft_addstr(ar)) == NULL || init(&data, ar, 0) == 0)
		return ;
	while (ar[++data.i] != 0 && ar[data.i][0] != '\0')
	{
		if (do_if(&data, ar, 0) == 0)
			return (print_error(5, MSGERROR, NULL, ar[data.i + 1]));
		if (do_if(&data, ar, 1) == 0)
			return (print_error(3, ar[data.i], NULL, NULL));
		else if (do_if(&data, ar, 2) == 0)
			return (print_error(3, ar[data.i], NULL, NULL));
		else if (do_if(&data, ar, 3) == 0)
			return (print_error(3, ar[data.i], NULL, NULL));
		else if (do_if(&data, ar, 4) == 0)
			return ;
		else if (do_if(&data, ar, 5) == 0)
			return ;
		else if (data.state++ == 0 &&
(data.cmd[ft_tablen((const char**)data.cmd) - 1] = ar[data.i]) == ar[data.i])
			if ((data.cmd = ft_addstr(data.cmd)) == NULL)
				return ;
	}
	endcuts(data);
}

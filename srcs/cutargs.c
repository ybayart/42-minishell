/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutargs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 23:02:56 by ybayart           #+#    #+#             */
/*   Updated: 2020/01/23 17:54:20 by ybayart          ###   ########.fr       */
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

static char	istoken(char *token)
{
	if (token[0] == '\0' ||
		ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0 ||
		ft_strcmp(token, "|") == 0 || ft_strcmp(token, ";") == 0)
		return (1);
	return (0);
}

static int	openfile(int fd, char *file, int init, int mode)
{
	if (fd != init)
		close(fd);
	if ((fd = open(file, mode, 0600)) == -1)
		return (-1);
	return (fd);
}

static void	make_redir(char state, int i, size_t len, int fd[2][2])
{
	static int	fd_bak[2][2];

	i++;
	if (state == 0 && len > 1)
	{
		if ((size_t)i < len && (fd_bak[1 - (i % 2)][1] = dup(1)) != -1)
			dup2(fd[1 - (i % 2)][1], 1);
		if ((size_t)i <= len && i >= 2 && (fd_bak[i % 2][0] = dup(0)) != -1)
			dup2(fd[i % 2][0], 0);
	}
	else if (len > 1)
	{
		if ((size_t)i < len)
		{
			close(fd[1 - (i % 2)][1]);
			dup2(fd_bak[1 - (i % 2)][1], 1);
		}
		if ((size_t)i <= len && i >= 2)
		{
			close(fd[i % 2][0]);
			dup2(fd_bak[i % 2][0], 0);
		}
	}
}

static char	init(char ***cmd, int *f_in, int *f_out)
{
	*cmd = NULL;
	if ((*cmd = addstr(*cmd)) == NULL)
		return (0);
	*f_in = 0;
	*f_out = 1;
	return (1);
}

void		cutargs(char **ar)
{
	int		i;
	int		j;
	int		f_in;
	int		f_out;
	int		fd[2][2];
	char	isredir;
	size_t	len;
	char	**cmd;

	i = -1;
	len = 1;
	while (ar[++i] != 0)
		if (ft_strcmp(ar[i], "|") == 0)
			len++;
	i = -1;
	j = -1;
	isredir = 0;
	if (init(&cmd, &f_in, &f_out) == 0)
		return ;
	while (ar[++i] != 0)
	{
		if (istoken(ar[i]) && istoken(ar[i + 1]) &&
		(ar[i][0] != '>' || ar[i + 1][0] != '>' || (istoken(ar[i + 2]) && i++)))
			return (print_error(5, MSGERROR, NULL, ar[i + 1]));
		if (ft_strcmp(ar[i], "<") == 0)
		{
			if ((f_in = openfile(f_in, ar[++i], 0, 0)) == -1)
				return (print_error(3, ar[i], NULL, NULL));
		}
		else if (ft_strcmp(ar[i], ">") == 0 && ar[i + 1] != 0 &&
				ft_strcmp(ar[i + 1], ">") == 0)
		{
			i++;
			if ((f_out = openfile(f_out, ar[++i], 1, 970)) == -1)
				return (print_error(3, ar[i], NULL, NULL));
		}
		else if (ft_strcmp(ar[i], ">") == 0)
		{
			if ((f_out = openfile(f_out, ar[++i], 1, 962)) == 0)
				return (print_error(3, ar[i], NULL, NULL));
		}
		else if (ft_strcmp(ar[i], "|") == 0)
		{
			if (cmd[ft_tablen((const char**)cmd) - 1][0] == '\0')
				cmd[ft_tablen((const char**)cmd) - 1] = 0;
			j++;
			pipe(fd[j % 2]);
			make_redir(0, j, len, fd);
			if (f_out != 1)
				run_touch();
			else
				space_cmd(cmd, ft_tablen((const char**)cmd), f_in, f_out);
			make_redir(1, j, len, fd);
			if (f_out != 1)
				space_cmd(cmd, ft_tablen((const char**)cmd), f_in, f_out);
			isredir = 1;
			if (init(&cmd, &f_in, &f_out) == 0)
				return ;
		}
		else if (ft_strcmp(ar[i], ";") == 0)
		{
			if (cmd[ft_tablen((const char**)cmd) - 1][0] == '\0')
				cmd[ft_tablen((const char**)cmd) - 1] = 0;
			space_cmd(cmd, ft_tablen((const char**)cmd), f_in, f_out);
			if (init(&cmd, &f_in, &f_out) == 0)
				return ;
		}
		else
		{
			cmd[ft_tablen((const char**)cmd) - 1] = ar[i];
			if ((cmd = addstr(cmd)) == NULL)
				return ;
		}
	}
	if (cmd[ft_tablen((const char**)cmd) - 1][0] == '\0')
		cmd[ft_tablen((const char**)cmd) - 1] = 0;
	if (isredir == 1)
	{
		j++;
		pipe(fd[j % 2]);
		make_redir(0, j, len, fd);
	}
	space_cmd(cmd, ft_tablen((const char**)cmd), f_in, f_out);
	if (isredir == 1)
	{
		make_redir(1, j, len, fd);
		isredir = 0;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:08:24 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/26 15:38:00 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	istoken(char *token)
{
	if (token[0] == '\0' ||
		ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0 ||
		ft_strcmp(token, "|") == 0 || ft_strcmp(token, ";") == 0)
		return (1);
	return (0);
}

int		openfile(int *fd, char *file, int init, int mode)
{
	if (*fd != init)
		close(*fd);
	if ((*fd = open(file, mode, 0600)) == -1)
		return (0);
	return (1);
}

void	make_redir(char state, int i, size_t len, int fd[2][2])
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

void	setfd(int f_in, int f_out, char state)
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

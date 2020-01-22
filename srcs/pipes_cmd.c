/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 13:51:53 by ybayart           #+#    #+#             */
/*   Updated: 2020/01/22 19:30:24 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/*static void	make_redir(char state, int i, size_t len, int fd[2][2])
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

void		pipes_cmd(char *line)
{
	int		i;
	int		fd[2][2];
	size_t	len;
	char	**cmd;

	if ((cmd = ft_split(line, '|')) == NULL)
		return ;
	len = ft_tablen((const char**)cmd);
	i = -1;
	if (len > 1)
		g_mini->redir = 1;
	while (cmd[++i])
	{
		if (pipe(fd[i % 2]) == -1)
			return (ft_free_tab((void**)cmd));
		make_redir(0, i, len, fd);
		redir_cmd(cmd[i]);
		make_redir(1, i, len, fd);
	}
	if (len > 1)
		g_mini->redir = 0;
	ft_free_tab((void**)cmd);
}*/

static char	*addchar(char *str, char c)
{
	int		i;
	size_t	len;
	char	*new;

	if (str == 0)
	{
		if ((new = malloc(sizeof(char) * 2)) == NULL)
			return (NULL);
		new[1] = '\0';
		new[0] = c;
	}
	else
	{
		len = ft_strlen(str);
		if ((new = malloc(sizeof(char) * (len + 2))) == NULL)
			return (NULL);
		new[len + 1] = '\0';
		i = -1;
		while (str[++i])
			new[i] = str[i];
		new[i] = c;
		free(str);
	}
	return (new);
}

static char	**addstr(char **tab)
{
	int		i;
	size_t	len;
	char	**new;

	if (tab == 0)
	{
		if ((new = malloc(sizeof(char*) * 2)) == NULL)
			return (NULL);
		new[1] = 0;
		len = 0;
	}
	else
	{
		len = ft_tablen((const char**)tab);
		if ((new = malloc(sizeof(char*) * (len + 2))) == NULL)
			return (NULL);
		new[len + 1] = 0;
		i = -1;
		while (tab[++i] != 0)
			new[i] = tab[i];
	}
	if ((new[len] = malloc(sizeof(char))) == NULL)
		return (NULL);
	new[len][0] = '\0';
	return (new);
}

void		pipes_cmd(char *line)
{
	int		i;
	int		j;
	char	quote[2];
	char	**args;

	args = NULL;
	if ((args = addstr(args)) == NULL)
		return ;
	i = -1;
	j = 0;
	quote[0] = 0;
	quote[1] = 0;
	while (line[++i])
	{
		if ((line[i] == ' ' || line[i] == '<' || line[i] == '>' || line[i] == '|') && quote[0] == 0 && quote[1] == 0)
		{
			if (args[j][0] != '\0')
			{
				j++;
				if ((args = addstr(args)) == NULL)
					return ;
			}
			if (line[i] != ' ')
			{
				if ((args[j] = addchar(args[j], line[i])) == NULL)
					return ;
				j++;
				if ((args = addstr(args)) == NULL)
					return ;
			}
		}
		else if (line[i] == '\'' && quote[1] == 0)
			quote[0] = (quote[0] == 1 ? 0 : 1);
		else if (line[i] == '"' && quote[0] == 0)
			quote[1] = (quote[1] == 1 ? 0 : 1);
		else if ((args[j] = addchar(args[j], line[i])) == NULL)
			return ;
	}
	i = -1;
	while (args[++i] != 0)
		printf("args[%d]: %s\n", i, args[i]);
}

/*
**static void	make_redir(char state, int i, size_t len, int fd[2][2])
**{
**	static int	fd_bak[2][2];
**
**	(void)len;
**	i++;
**	if (state == 0 && len > 1)
**	{
**		if ((size_t)i < len)
**		{
**			fd_bak[1 - (i % 2)][1] = dup(1);
**			dup2(fd[1 - (i % 2)][1], 1);
**			write(2, "sortie redir ", 13);
**			ft_putnbr_fd(1 - (i % 2), 2);
**			write(2, "\n", 1);
**		}
**		if ((size_t)i <= len && i >= 2)
**		{
**			fd_bak[i % 2][0] = dup(0);
**			dup2(fd[i % 2][0], 0);
**			write(2, "entree redir ", 13);
**			ft_putnbr_fd(i % 2, 2);
**			write(2, "\n", 1);
**		}
**	}
**	else if (len > 1)
**	{
**		if ((size_t)i < len)
**		{
**				close(fd[1 - (i % 2)][1]);
**				write(2, "close sortie ", 13);
**				ft_putnbr_fd(1 - (i % 2), 2);
**				write(2, "\n", 1);
**			dup2(fd_bak[1 - (i % 2)][1], 1);
**			write(2, "sortie end ", 11);
**			ft_putnbr_fd(1 - (i % 2), 2);
**			write(2, "\n", 1);
**		}
**		if ((size_t)i <= len && i >= 2)
**		{
**				close(fd[i % 2][0]);
**				write(2, "close entree ", 13);
**				ft_putnbr_fd(i % 2, 2);
**				write(2, "\n", 1);
**			dup2(fd_bak[i % 2][0], 0);
**			write(2, "entree end ", 11);
**			ft_putnbr_fd(i % 2, 2);
**			write(2, "\n", 1);
**		}
**	}
**}
**
**void		redir_cmd(char *line)
**{
**	int		i;
**	int		fd[2][2];
**	size_t	len;
**	char	**cmd;
**
**	if ((cmd = ft_splits(line, "|<>")) == NULL)
**		return ;
**	len = ft_tablen((const char**)cmd);
**	i = -1;
**	if (pipe(fd[1]) == -1)
**		return (ft_free_tab((void**)cmd));
**	while (cmd[++i])
**	{
**		if (pipe(fd[i % 2]) == -1)
**			return (ft_free_tab((void**)cmd));
**		ft_putnbr_fd(i, 2);
**		write(2, "\n", 1);
**		make_redir(0, i, len, fd);
**		write(2, "cmd: ", 5);
**		write(2, cmd[i], ft_strlen(cmd[i]));
**		write(2, "\n", 1);
**		space_cmd(cmd[i]);
**		write(2, "cmd exec\n", 9);
**		make_redir(1, i, len, fd);
**	}
**}
*/

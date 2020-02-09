/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getargs_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 13:51:53 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/10 00:24:19 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char		*addchar(char *str, char c)
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

char		**addstr(char **tab)
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
	new[len] = ft_strdup("\0");
	return (new);
}

static char	setnewline(char ***args, int *j, char c)
{
	if ((*args)[*j][0] != '\0')
	{
		(*j)++;
		if (((*args) = addstr(*args)) == NULL)
			return (0);
	}
	if (!ft_isspace(c))
	{
		if (((*args)[*j] = addchar((*args)[*j], c)) == NULL)
			return (0);
		(*j)++;
		if ((*args = addstr(*args)) == NULL)
			return (0);
	}
	return (1);
}

static char	loop(char ***args, char *l, int (*i)[2], char (*qt)[3])
{
	if ((ft_isspace(l[(*i)[0]]) || l[(*i)[0]] == '<' ||
		l[(*i)[0]] == '>' || l[(*i)[0]] == '|' || l[(*i)[0]] == ';') &&
		(*qt)[0] == 0 && (*qt)[1] == 0)
	{
		if ((*qt)[2] == 1 && wildcard(args, &(*i)[1], (*i)[1]) == 0)
			return (0);
		(*qt)[2] = 0;
		if (setnewline(args, &(*i)[1], l[(*i)[0]]) == 0)
			return (0);
	}
	else if (l[(*i)[0]] == '\'' && (*qt)[1] == 0)
		(*qt)[0] = ((*qt)[0] == 1 ? 0 : 1);
	else if (l[(*i)[0]] == '"' && (*qt)[0] == 0)
		(*qt)[1] = ((*qt)[1] == 1 ? 0 : 1);
	else if ((l[(*i)[0]] == '\\' && ((*qt)[2] = -1) == -1) && ((((*qt)[0] == 1
	&& l[(*i)[0] + 1] == '\'') || ((*qt)[1] == 1 && l[(*i)[0] + 1] == '"'))
	|| ((*qt)[0] == 0 && (*qt)[1] == 0)) && (*i)[0]++ == -1)
		;
	else if ((*qt)[2] != -1 && (*qt)[0] == 0 && (*qt)[1] == 0 && ((*i)[0] == 0
	|| l[(*i)[0] - 1] != '\\') && l[(*i)[0]] == '*' && ((*qt)[2] = 1) == 2)
		;
	else if (((*args)[(*i)[1]] = addchar((*args)[(*i)[1]], l[(*i)[0]])) == NULL)
		return (0);
	return (1);
}

void		getargs_cmd(char *line)
{
	int		i[2];
	char	qt[3];
	char	**args;

	args = NULL;
	if ((args = addstr(args)) == NULL)
		return ;
	i[0] = -1;
	i[1] = 0;
	qt[0] = 0;
	qt[1] = 0;
	qt[2] = 0;
	while (line[++i[0]])
		if (loop(&args, line, &i, &qt) == 0)
			return ;
	if (qt[2] == 1 && wildcard(&args, &i[1], i[1]) == 0)
		return ;
	if (args[i[1]] != 0 && args[i[1]][0] == '\0')
		args[i[1]] = 0;
	i[0] = -1;
	while (args[++i[0]] != 0)
		if (args[i[0]][0] == '~' && (args[i[0]] = ft_strfrjoin(
	ft_lst_find_env(&g_mini->env, "HOME"), args[i[0]] + 1, args[i[0]])) == NULL)
			return ;
	cutargs(args);
}

/*
**static void	make_redir(char state, int i, size_t len, int fd[2][2])
**{
**	static int	fd_bak[2][2];
**
**	i++;
**	if (state == 0 && len > 1)
**	{
**		if ((size_t)i < len && (fd_bak[1 - (i % 2)][1] = dup(1)) != -1)
**			dup2(fd[1 - (i % 2)][1], 1);
**		if ((size_t)i <= len && i >= 2 && (fd_bak[i % 2][0] = dup(0)) != -1)
**			dup2(fd[i % 2][0], 0);
**	}
**	else if (len > 1)
**	{
**		if ((size_t)i < len)
**		{
**			close(fd[1 - (i % 2)][1]);
**			dup2(fd_bak[1 - (i % 2)][1], 1);
**		}
**		if ((size_t)i <= len && i >= 2)
**		{
**			close(fd[i % 2][0]);
**			dup2(fd_bak[i % 2][0], 0);
**		}
**	}
**}
**
**void		pipes_cmd(char *line)
**{
**	int		i;
**	int		fd[2][2];
**	size_t	len;
**	char	**cmd;
**
**	if ((cmd = ft_split(line, '|')) == NULL)
**		return ;
**	len = ft_tablen((const char**)cmd);
**	i = -1;
**	if (len > 1)
**		g_mini->redir = 1;
**	while (cmd[++i])
**	{
**		if (pipe(fd[i % 2]) == -1)
**			return (ft_free_tab((void**)cmd));
**		make_redir(0, i, len, fd);
**		redir_cmd(cmd[i]);
**		make_redir(1, i, len, fd);
**	}
**	if (len > 1)
**		g_mini->redir = 0;
**	ft_free_tab((void**)cmd);
**}
*/

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

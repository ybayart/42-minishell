/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 18:49:13 by ybayart           #+#    #+#             */
/*   Updated: 2020/01/18 18:38:46 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

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

static int	init_cmd(char **(*args)[2], int (*j)[2], int *state)
{
	int		i;

	i = -1;
	while (++i < 2)
	{
		(*args)[i] = NULL;
		if (((*args)[i] = addstr((*args)[i])) == NULL)
			return (0);
		(*j)[i] = 0;
	}
	*state = 0;
	return (-1);
}

void		redir_exec(char **args, char **files)
{
	size_t	len;
	int		i;
	int		fd[2];

	len = ft_tablen((const char**)args);
	if (args[len - 1][0] == '\0')
		args[len - 1] = 0;
	if (((len = ft_tablen((const char**)files)) == 1 && files[0][0] == '\0')
					|| g_mini->redir == 1)
		space_cmd(args, ft_tablen((const char**)args));
	if ((i = -1) == -1 && files[len - 1][0] == '\0')
		files[len - 1] = 0;
	while (files[++i])
	{
		fd[0] = dup(1);
		if ((fd[1] = open(files[i], O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
			print_error(2, files[i]);
		else if (dup2(fd[1], 1) != -1)
		{
			space_cmd(args, ft_tablen((const char**)args));
			dup2(fd[0], 1);
		}
	}
	ft_free_tab((void**)args);
	ft_free_tab((void**)files);
}

void		redir_cmd(char *line)
{
	int		i;
	int		j[2];
	int		state;
	char	**args[2];

	if ((i = init_cmd(&args, &j, &state)) == 0)
		return ;
	while (line[++i])
		if (line[i] == ' ')
		{
			if (args[state][j[state]][0] != '\0')
			{
				j[state]++;
				if ((args[state] = addstr(args[state])) == NULL)
					return ;
			}
			state = 0;
		}
		else if (line[i] == '>')
			while ((state = 1) == 1 && line[i + 1] == ' ')
				i++;
		else if ((args[state][j[state]] = addchar(args[state][j[state]],
									line[i])) == NULL)
			return ;
	redir_exec(args[0], args[1]);
}

/*
**void	redir_cmd(char *line)
**{
**	int		i;
**	int		fd[2];
**	size_t	len;
**	char	**cmd;
**	char	**tmp;
**
**	if ((cmd = ft_split(line, '>')) == NULL)
**		return ;
**	len = ft_tablen(cmd);
**	i = -1;
**	while (cmd[++i] != 0)
**	{
**		if (i == 0)
**		{
**			if ((tmp = ft_split(cmd[i], ' ')) == NULL)
**				return (ft_free_tab((void**)cmd));
**			if (len > 1)
**			{
**				fd[0] = dup(1);
**				dup2(fd[1], 1);
**			}
**		}
**		else
**		{
**			fd[0] = dup(1);
**			if ((fd[1] = open(
**			dup2(fd[1], 1);
**			space_cmd(tmp);
**		}
**	}
**	if (len > 1)
**	{
**		dup2(fd[0], 1);
**		close(fd[0]);
**	}
**	ft_free_tab((void**)cmd);
**}
*/
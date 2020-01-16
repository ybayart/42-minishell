/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:53:01 by racohen           #+#    #+#             */
/*   Updated: 2020/01/16 19:12:40 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/*
**static char	*parent_path(char *path)
**{
**	size_t	i;
**	char	*new;
**
**	i = ft_strlen(path);
**	while (--i > 0)
**	{
**		if (path[i] == '/')
**			break ;
**	}
**	if ((new = malloc(sizeof(char) * (i + 1))) == NULL)
**		return (NULL);
**	new[i] = '\0';
**	while (i-- > 0)
**		new[i] = path[i];
**	free(path);
**	return (new);
**}
**
**void		run_cd(const char *bin, char **argv, char **env)
**{
**	char	**dirs;
**	char	*path;
**	int		i;
**	int		modif;
**
**	modif = 0;
**	if (argv[1] == 0 && (modif = 1))
**	{
**		if ((path = ft_strdup(ft_lst_find_env(&g_mini->env, "HOME"))) == NULL)
**			return ;
**	}
**	else
**	{
**		if ((dirs = ft_split(argv[1], '/')) == NULL)
**			return ;
**		i = -1;
**		if ((path = ft_strdup(ft_lst_find_env(&g_mini->env, "PWD"))) == NULL)
**			return ;
**		while (dirs[++i])
**		{
**			if (ft_strcmp(dirs[i], "..") == 0)
**			{
**				if ((path = parent_path(path)) == NULL)
**					return ;
**				modif = 1;
**			}
**			else if (opendir(dirs[i]) != NULL && (modif = 1))
**				ft_printf("yes\n");
**		}
**	}
**	if (modif)
**	{
**		chdir(path);
**		ft_lst_replace_env(&g_mini->env, "OLDPWD",
**			ft_strdup(ft_lst_find_env(&g_mini->env, "PWD")));
**		ft_lst_replace_env(&g_mini->env, "PWD", path);
**	}
**	(void)bin;
**	(void)env;
**}
*/

void		run_cd(const char *bin, char **argv, char **env)
{
	if (argv[1] == 0)
		chdir(ft_lst_find_env(&g_mini->env, "HOME"));
	else
	{
		if (strncmp(argv[1], "~/", 2) == 0 ||
			(ft_strlen(argv[1]) == 1 && argv[1][0] == '~'))
		{
			chdir(ft_lst_find_env(&g_mini->env, "HOME"));
			if (strncmp(argv[1], "~/", 2) == 0)
				argv[1] += 2;
			else
				argv[1]++;
		}
		if (ft_strlen(argv[1]) > 0 && chdir(argv[1]) == -1)
			ft_printf("%s: %s: %s\n", bin, strerror(errno), argv[1]);
	}
	ft_lst_replace_env(&g_mini->env, "OLDPWD",
				ft_strdup(ft_lst_find_env(&g_mini->env, "PWD")));
	ft_lst_replace_env(&g_mini->env, "PWD", ft_strdup(getcwd(NULL, 0)));
	(void)env;
}

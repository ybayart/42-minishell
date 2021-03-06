/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:39:20 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/27 12:47:19 by yanyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	utils_space_cmd(char ***cmd, size_t i, char *path)
{
	char	**res;

	if ((res = (char**)malloc(sizeof(char*) * (i + 1))) == NULL)
		return ;
	res[i] = 0;
	i = -1;
	while ((*cmd)[++i])
		res[i] = ft_strdup((*cmd)[i]);
	res = replace_quote_path(res);
	ft_free_tab((void**)(*cmd));
	if (check_builtins(path))
		run_builtins(path, res);
	else
		run_cmd(path, res, ft_list_to_tab_env(g_mini->env));
	free(path);
	ft_free_tab((void**)res);
}

void	utils_shell_do(char **line)
{
	char	*tmp;
	size_t	len;

	add_history((*line));
	if ((tmp = ft_strndup((*line), 1)) != NULL && istoken(tmp))
		print_error(5, "syntax error near unexpected token", NULL, tmp);
	else
	{
		ft_strreplace(line, ft_strdup("$?"), ft_itoa(g_mini->last_exit));
		if (tmp != NULL)
			free(tmp);
		tmp = NULL;
		if ((*line)[(len = ft_strlen((*line)) - 1)] == ';'
				&& len > 0 && (*line)[len - 1] != ';')
			(*line)[len] = '\0';
		getargs_cmd((*line));
		while (g_mini->exec > 0)
		{
			waitpid(-1, &g_mini->last_exit, 0);
			g_mini->last_exit = WEXITSTATUS(g_mini->last_exit);
			g_mini->exec--;
		}
	}
	if (tmp != NULL)
		free(tmp);
}

void	utils_shell(char **line)
{
	if (g_mini->signal == 1)
	{
		free((*line));
		(*line) = NULL;
		g_mini->signal = 0;
	}
	if ((*line) == NULL)
		(*line) = ft_strdup("");
}

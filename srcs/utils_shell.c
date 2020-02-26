/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:39:20 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/26 15:53:21 by ybayart          ###   ########.fr       */
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

	add_history((*line));
	g_mini->exec = 1;
	if ((tmp = ft_strndup((*line), 1)) != NULL && istoken(tmp))
		print_error(5, "syntax error near unexpected token", NULL, tmp);
	else
	{
		if (tmp != NULL)
			free(tmp);
		tmp = NULL;
		getargs_cmd((*line));
	}
	if (tmp != NULL)
		free(tmp);
}

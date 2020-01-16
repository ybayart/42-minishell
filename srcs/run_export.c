/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:56:00 by racohen           #+#    #+#             */
/*   Updated: 2020/01/16 15:15:01 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	change(char *name, char *value)
{
	t_list_env	*tmp;

	tmp = g_mini->env;
	while (tmp)
	{
		if (strcmp(tmp->name, name) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
		}
		tmp = tmp->next;
	}
}

/*
**if variable already exist don't add new
*/

void	run_export(const char *bin, char **argv, char **env)
{
	int		i;
	char	**tmp;
//	char	**re;

	(void)bin;
	(void)argv;
	(void)env;
	i = 0;
	while (argv[++i])
	{
		if ((tmp = ft_split(argv[i], '=')) == NULL)
			return ;
//		re = replace_quote_path(tmp);
//		printf("%s\n", re[1]);
//		free(tmp[1]);
//		tmp[1] = ft_strdup(re[1]);
//		ft_free_tab((void**)re);
		if (ft_lst_find_env(&g_mini->env, tmp[0]))
			change(tmp[0], tmp[1]);
		else
			ft_lst_add_env(&g_mini->env, ft_lst_new_env(tmp[0], tmp[1]));
//		ft_free_tab((void**)tmp);
	}
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:56:00 by racohen           #+#    #+#             */
/*   Updated: 2020/03/03 21:00:02 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		check_quote_err(char *name)
{
	while (*name != '\'')
		if (*name++ == '\0')
			return (0);
	return (1);
}

void	change(t_list_env **env, char *name, char *value)
{
	t_list_env	*tmp;

	tmp = *env;
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

void	exe(char **tmp)
{
	if (ft_lst_find_env(&g_mini->env, tmp[0]) != NULL)
		change(&g_mini->env, tmp[0], (tmp[1] == 0 ? "" : tmp[1]));
	else if (tmp[1] == 0)
		ft_lst_add_env(&g_mini->env, ft_lst_new_env(ft_strdup(tmp[0]),
			ft_strdup("")));
	else
		ft_lst_add_env(&g_mini->env, ft_lst_new_env(ft_strdup(tmp[0]),
			ft_strdup(tmp[1])));
}

void	run_env_export(void)
{
	t_list_env	*list;

	list = g_mini->env;
	while (list)
	{
		write(1, "declare -x ", 11);
		write(1, list->name, ft_strlen(list->name));
		write(1, "=\"", 2);
		write(1, list->value, ft_strlen(list->value));
		write(1, "\"\n", 2);
		list = list->next;
	}
	return ;
}

void	run_export(char **argv)
{
	int		i;
	char	**tmp;

	i = 0;
	if (argv[i + 1] == 0)
	{
		ft_list_sort_env(&(g_mini->env));
		run_env_export();
	}
	while (argv[++i])
	{
		if (!(tmp = ft_split(argv[i], '=')) || !ft_strchr(argv[i], '='))
		{
			ft_free_tab((void**)tmp);
			return ;
		}
		if (tmp[0] == 0)
		{
			ft_free_tab((void**)tmp);
			return (print_error(4, "`='", "export", "not a valid identifier"));
		}
		if (check_quote_err(tmp[0]))
		{
			ft_free_tab((void**)tmp);
			return (print_error(4, argv[i], "export", "not valid identifier"));
		}
		exe(tmp);
		ft_free_tab((void**)tmp);
	}
}

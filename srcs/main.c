/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 13:40:14 by racohen           #+#    #+#             */
/*   Updated: 2020/01/16 19:28:05 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int			ft_free_all(t_mini *mini)
{
	if (mini)
		free(mini);
	return (EXIT_FAILURE);
}

t_list_env	*init_env(char *const envp[])
{
	int			i;
	char		**tmp;
	t_list_env	*env;
	t_list_env	*elem;

	i = -1;
	while (envp[++i])
	{
		if ((elem = (t_list_env*)malloc(sizeof(t_list_env))) == NULL)
			return (NULL);
		if ((tmp = ft_split(envp[i], '=')) == NULL)
			return (NULL);
		ft_lst_add_env(&env,
			ft_lst_new_env(ft_strdup(tmp[0]), ft_strdup(tmp[1])));
	}
	return (env);
}

t_mini		*init_struct(char *const envp[])
{
	if ((g_mini = (t_mini*)malloc(sizeof(t_mini))) == NULL)
		return (NULL);
	if ((g_mini->env = init_env(envp)) == NULL)
		return (NULL);
	g_mini->alive = 1;
	g_mini->last_exit = 0;
	g_mini->out = NULL;
	g_mini->in = NULL;
	g_mini->signal = 0;
	return (g_mini);
}

int			main(int argc, char *const argv[], char *const envp[])
{
	if ((g_mini = init_struct(envp)) == NULL)
		return (ft_free_all(g_mini));
	if (shell() == EXIT_FAILURE)
		return (ft_free_all(g_mini));
	ft_free_all(g_mini);
	(void)argc;
	(void)argv;
	return (EXIT_SUCCESS);
}

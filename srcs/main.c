/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 13:40:14 by racohen           #+#    #+#             */
/*   Updated: 2019/11/30 09:51:35 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

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
	if ((mini = (t_mini*)malloc(sizeof(t_mini))) == NULL)
		return (NULL);
	if ((mini->env = init_env(envp)) == NULL)
		return (NULL);
	mini->alive = 1;
	mini->last_exit = 0;
	mini->out = NULL;
	mini->in = NULL;
	return (mini);
}

int			main(int argc, char *const argv[], char *const envp[])
{
	if ((mini = init_struct(envp)) == NULL)
		return (ft_free_all(mini));
	if (shell() == EXIT_FAILURE)
		return (ft_free_all(mini));
	ft_free_all(mini);
	(void)argc;
	(void)argv;
	return (EXIT_SUCCESS);
}

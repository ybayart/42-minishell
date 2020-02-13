/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 13:40:14 by racohen           #+#    #+#             */
/*   Updated: 2020/02/13 19:47:51 by ybayart          ###   ########.fr       */
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
	env = NULL;
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
	g_mini->redir = 0;
	return (g_mini);
}

void		enableRawMode(void)
{
	struct termios	raw;

	tgetent(NULL, getenv("TERM"));
	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ICANON);
	raw.c_lflag &= ~(ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	g_mini->typed_pos = 0;
	g_mini->typed = NULL;
}

int			main(int argc, char *const argv[], char *const envp[])
{
	if ((g_mini = init_struct(envp)) == NULL)
		return (ft_free_all(g_mini));
	enableRawMode();
	if (shell() == EXIT_FAILURE)
		return (ft_free_all(g_mini));
	ft_free_all(g_mini);
	(void)argc;
	(void)argv;
	return (EXIT_SUCCESS);
}

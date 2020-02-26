/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 13:40:14 by racohen           #+#    #+#             */
/*   Updated: 2020/02/26 14:25:42 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	init_env(char *const envp[])
{
	int			i;
	char		**tmp;

	i = -1;
	while (envp[++i])
	{
		if ((tmp = ft_split(envp[i], '=')) == NULL)
			return (0);
		ft_lst_add_env(&(g_mini->env),
			ft_lst_new_env(ft_strdup(tmp[0]),
				ft_strdup(tmp[1] == 0 ? "" : tmp[1])));
		ft_free_tab((void**)tmp);
	}
	return (1);
}

char	init_struct(char *const envp[])
{
	if ((g_mini = (t_mini*)malloc(sizeof(t_mini))) == NULL)
		return (0);
	g_mini->env = NULL;
	if (init_env(envp) == 0)
		return (0);
	g_mini->alive = 1;
	g_mini->last_exit = 0;
	g_mini->out = NULL;
	g_mini->in = NULL;
	g_mini->signal = 0;
	g_mini->redir = 0;
	g_mini->ispipe = 0;
	g_mini->typed_pos = 0;
	g_mini->typed = NULL;
	g_mini->history_pos = -1;
	g_mini->history = NULL;
	g_mini->current = ft_strdup("");
	print_prompt(0);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	return (1);
}

void	raw_mode(void)
{
	struct termios	raw;

	tgetent(NULL, getenv("TERM"));
	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ICANON);
	raw.c_lflag &= ~(ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void	init_mode(void)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int		main(int argc, char *const argv[], char *const envp[])
{
	int		ret;
//	pid_t	pid;
//	int		status;

//	status = 0;
//	if ((pid = fork()) == -1)
//		exit(EXIT_FAILURE);
//	else if (pid != 0)
//	{
//		waitpid(pid, &status, 0);
//		exit(WEXITSTATUS(status));
//	}
	if (init_struct(envp) == 0 || get_history() == 0)
		exit(EXIT_FAILURE);
	raw_mode();
	ret = EXIT_SUCCESS;
	if (shell() == EXIT_FAILURE)
		ret = EXIT_FAILURE;
	endofprog();
	(void)argc;
	(void)argv;
	exit(ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 15:49:11 by racohen           #+#    #+#             */
/*   Updated: 2019/12/04 19:21:29 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static void	print_prompt(t_list_env *list)
{
	ft_printf("%s> ", ft_lst_find_env(&list, PWD));
}

void sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		signal(signo, SIG_IGN);
		signal(SIGINT, sig_handler);
		write(1, "\n", 1);
		print_prompt(mini->env);
	}
}

static void space_cmd(char *line)
{
	int		i;
	char	*path;
	char	**res;
	char	**cmd;

	if ((cmd = ft_split(line, ' ')) == NULL)
		return ;
	free(line);
	i = ft_get_len(cmd);
	if (check_builtins(cmd[0]))
		path = ft_strdup(cmd[0]);
	else if ((path = search_bin((char*)cmd[0], ft_lst_find_env(&mini->env, PATH))) == NULL)
	{
		ft_printf("zsh: command not found: %s\n", cmd[0]);
		mini->last_exit = 127;
		return ;
	}
	if (ft_strcmp(cmd[0], "export") != 0)
		cmd = replace_quote_path(cmd);
	if ((res = (char**)malloc(sizeof(char*) * (i + 1))) == NULL)
		return ;
	res[i] = 0;
	i = -1;
	while (cmd[++i])
		res[i] = cmd[i];
	run_cmd(path, res, ft_list_to_tab_env(mini->env));
	ft_free_tab((void**)cmd);
	free(res);
}

static void hold_cmd(char *line)
{
	int		i;
	char	**cmd;

	i = -1;
	if ((cmd = ft_split(line, ';')) == NULL)
		return ;
	free(line);
	while (cmd[++i])
	{
		if (strncmp(cmd[i], "exit", ft_strlen(cmd[0])) == 0)
		{
			mini->alive = 0;
			return ;
		}
		space_cmd(cmd[i]);
	}
	ft_free_tab((void**)cmd);
}

int			shell()
{
	char	*line;

	if ((line = ft_strdup("")) == NULL)
		return (EXIT_FAILURE);
	signal(SIGINT, sig_handler); 
	while (mini->alive)
	{	
		print_prompt(mini->env);
		if ((get_next_line(0, &line)) == -1)
			exit(EXIT_FAILURE);
		hold_cmd(line);
	}
	return (EXIT_SUCCESS);
}

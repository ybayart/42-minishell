/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 21:25:58 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/26 10:18:43 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	add_history(char *line)
{
	int		fd;
	char	*file;

	file = ft_strjoin(ft_lst_find_env(&g_mini->env, "HOME"),
											"/.minishell_history");
	if ((fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0600)) != -1)
	{
		ft_lstadd_front(&(g_mini->history), ft_lstnew(ft_strdup(line)));
		g_mini->history_pos = -1;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		close(fd);
	}
	free(file);
}

char	get_history(void)
{
	int		fd;
	int		ret;
	char	*file;
	char	*line;

	file = ft_strjoin(ft_lst_find_env(&g_mini->env, "HOME"),
											"/.minishell_history");
	if ((fd = open(file, 0, 0600)) != -1)
	{
		line = NULL;
		while ((ret = get_next_line(fd, &line)) == 1)
		{
			ft_lstadd_front(&(g_mini->history), ft_lstnew(line));
			line = NULL;
		}
		free(line);
		close(fd);
	}
	free(file);
	return (1);
}

void	set_history(char c)
{
	char	*line;

	if (c == 65)
	{
		if (g_mini->history_pos >= ft_lstsize(g_mini->history) - 1)
			return ;
		line = ft_lstget_at(g_mini->history, ++(g_mini->history_pos))->content;
	}
	else
	{
		if (g_mini->history_pos <= 0)
		{
			line = g_mini->current;
			g_mini->history_pos = -1;
		}
		else
			line = ft_lstget_at(g_mini->history,
					--(g_mini->history_pos))->content;
	}
	g_mini->typed_pos = (int)ft_strlen(line);
	ft_lst_clear_typed(&(g_mini->typed));
	ft_lst_push_str_typed(&(g_mini->typed), line);
	write(1, "\r", 1);
	print_term("ce", 1);
}

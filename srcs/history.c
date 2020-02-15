/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 21:25:58 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/15 21:41:51 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	add_history(char *line)
{
	int		fd;
	char	*file;

	file = ft_strjoin(ft_lst_find_env(&g_mini->env, "HOME"),
											"/.minishell_history");
	if ((fd = open(file, 970, 0600)) != -1)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		close(fd);
	}
	free(file);
}

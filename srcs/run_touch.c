/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_touch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:36:59 by ybayart           #+#    #+#             */
/*   Updated: 2020/01/23 17:41:11 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	run_touch(void)
{
	char	**cmd;

	if ((cmd = malloc(sizeof(char*) * 3)) == NULL)
		return ;
	cmd[0] = ft_strdup("touch");
	cmd[1] = ft_strdup("/tmp/minishell");
	cmd[2] = 0;
	space_cmd(cmd, 2, 0, 1);
	free(cmd[0]);
	free(cmd[1]);
	free(cmd);
}

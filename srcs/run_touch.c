/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_touch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:36:59 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/25 17:03:20 by ybayart          ###   ########.fr       */
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
	space_cmd(&cmd, 0, 1);
}
